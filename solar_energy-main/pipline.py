import pandas as pd
import numpy as np
import tensorflow as tf
import keras
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import OneHotEncoder
from generate_features import generate_features, generate_time_features
from keras.metrics import RootMeanSquaredError, MeanAbsoluteError
from predict import predict
import xgboost as xgb
from sklearn.metrics import mean_squared_error as MSE


SIMPLE = False
LAT, LON = 55.775588, 37.605662  # latitude, longitude
year = 2022
month = 7
day = 13

data = pd.read_csv("solar1.csv")
if not SIMPLE:
    data = generate_features(
        LAT=LAT, LON=LON, data=data, year=year, month=month, day=day
    )
data = generate_time_features(data)
# time categories: hour, minutes
categories = [
    np.array(list(range(-1, 24))),
    np.array(list(range(60))),
]
ohe = OneHotEncoder(categories=categories)
X = np.hstack(
    [
        data.drop(columns="nv").to_numpy(),
        ohe.fit_transform(data[["hour", "minute"]]).todense(),
    ]
)
y = data.nv
y = y.to_numpy()

X_train, X_val, y_train, y_val = train_test_split(
    X, y, test_size=0.33, shuffle=False, random_state=42
)

dataset_train = tf.data.Dataset.from_tensor_slices((X_train, y_train))
dt_b = dataset_train.shuffle(buffer_size=1024).batch(batch_size=256)
dataset_val = tf.data.Dataset.from_tensor_slices((X_val, y_val))
dv_b = dataset_val.batch(batch_size=256)

for batch in dataset_train.take(1):
    inputs, targets = batch
print("Input shape:", inputs.numpy().shape)
print("Target shape:", targets.numpy().shape)

# linear regression : linear_regression_l11000.0_l21000.0
linear_regression = keras.models.Sequential(
    [
        keras.layers.Dense(
            input_shape=inputs.shape,
            units=1, kernel_regularizer=keras.regularizers.l1_l2(l1=10**3, l2=10**3)
        )
    ]
)

linear_regression.compile(
    optimizer=keras.optimizers.Adam(learning_rate=0.1**2),
    loss="mse",
    metrics=[
        RootMeanSquaredError(name="root_mean_squared_error", dtype=None),
        MeanAbsoluteError(name="mean_absolute_error", dtype=None),
    ],
)

path_checkpoint = f"linear_regression_l11000.0_l21000.0.h5"

es_callback = keras.callbacks.EarlyStopping(
    monitor="val_loss", min_delta=0, patience=10
)
modelckpt_callback = keras.callbacks.ModelCheckpoint(
    monitor="val_loss",
    filepath=path_checkpoint,
    verbose=0,
    save_weights_only=True,
    save_best_only=True,
)

history_linear_regression = linear_regression.fit(
    dt_b,
    epochs=10000,
    validation_data=dv_b,
    callbacks=[es_callback, modelckpt_callback],
    verbose=0,
)
print("\n")
print("\n")
print("\n")
print(
    "Predict on 31.07.2022 20000, 40000 secs:",
    predict(
        seconds=[20000, 40000], year=2022, month=7, day=31, model=linear_regression
    ),
)
print("\n")
print("\n")
print("\n")

### MLP

mlp_model = tf.keras.Sequential(
    [
        #     keras.layers.BatchNormalization(axis=0),
        keras.layers.Dense(
            input_shape=inputs.shape,
            units=32,
            activation="relu",
            kernel_regularizer=keras.regularizers.l1_l2(l1=10**3, l2=10**3),
        ),
        keras.layers.Dropout(0.2),
        keras.layers.Dense(
            units=128,
            activation="relu",
            kernel_regularizer=keras.regularizers.l1_l2(l1=10**3, l2=10**3),
        ),
        keras.layers.Dropout(0.4),
        keras.layers.Dense(
            units=32,
            activation="relu",
            kernel_regularizer=keras.regularizers.l1_l2(l1=10**3, l2=10**3),
        ),
        keras.layers.Dropout(0.4),
        keras.layers.Dense(
            units=16,
            activation="relu",
            kernel_regularizer=keras.regularizers.l1_l2(l1=10**3, l2=10**3),
        ),
        keras.layers.Dense(units=1),
    ]
)
mlp_model.compile(
    optimizer=keras.optimizers.Adam(learning_rate=0.1**3),
    loss="mse",
    metrics=[
        RootMeanSquaredError(name="root_mean_squared_error", dtype=None),
        MeanAbsoluteError(name="mean_absolute_error", dtype=None),
    ],
)
mlp_model.summary()


path_checkpoint = f"multilayer_perceptron.h5"

es_callback = keras.callbacks.EarlyStopping(
    monitor="val_loss", min_delta=0, patience=10
)
modelckpt_callback = keras.callbacks.ModelCheckpoint(
    monitor="val_loss",
    filepath=path_checkpoint,
    verbose=1,
    save_weights_only=True,
    save_best_only=True,
)

history_mlp = mlp_model.fit(
    dt_b,
    epochs=10000,
    validation_data=dv_b,
    callbacks=[es_callback, modelckpt_callback],
    verbose=0,
)
print("\n")
print("\n")
print("\n")
print(
    "Predict on 31.07.2022 20000, 40000 secs:",
    predict(seconds=[20000, 40000], year=2022, month=7, day=31, model=mlp_model),
)
print("\n")
print("\n")
print("\n")
### Xgboost
# https://stackoverflow.com/questions/40418612/xgboost-on-android

best_params = {
    "max_depth": 12,
    "booster": "gbtree",
    "reg_alpha": 0.1,
    "reg_lambda": 10000.0,
    "colsample_bytree": 0,
    "min_child_weight": 10,
    "objective": "reg:squarederror",
}

xgb_best = xgb.XGBRegressor(
    **best_params,
    early_stopping_rounds=6,
    seed=142,
    eval_metric="rmse",
)
xgb_best.fit(
    X_train, y_train, eval_set=[(X_train, y_train), (X_val, y_val)], verbose=True
)
pred = xgb_best.predict(X_val)

# RMSE Computation
rmse = np.sqrt(MSE(y_val, pred))
print("RMSE : % f" % (rmse))

print(
    "Predict on 31.07.2022 20000, 40000 secs:",
    predict(seconds=[20000, 40000], year=2022, month=7, day=31, model=xgb_best),
)
