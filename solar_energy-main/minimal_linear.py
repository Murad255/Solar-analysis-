from predict import predict
# linear regression
from tensorflow import keras
linear_regression = keras.models.Sequential(
    [
        keras.layers.Dense(
            input_shape=(98,),
            units=1, kernel_regularizer=keras.regularizers.l1_l2(l1=10**3, l2=10**3)
        )
    ]
)
linear_regression.compile(
    optimizer=keras.optimizers.Adam(learning_rate=0.1**2),
    loss="mse",
)
linear_regression.load_weights('linear_regression_l11000.0_l21000.0.h5')
print(
    "Predict on 31.07.2022 20000, 40000 secs:",
    predict(seconds=[20000, 40000], year=2022, month=7, day=31, model=linear_regression),
)