from typing import List, Union

import pandas as pd
import numpy as np
from sklearn.preprocessing import OneHotEncoder
from generate_features import generate_features, generate_time_features

SIMPLE = False

def predict(seconds: Union[int, List[int]], year: int, month: int, day: int, model):
    """input:
    seconds:int/list number of seconds from day beginning
    year:int, month:int, day:int
    output:np.array
    """
    LAT, LON = 55.775588, 37.605662  # latitude, longitude
    if type(seconds) == int:
        data = pd.DataFrame({"nv": [0], "sec": [seconds]})
    elif type(seconds) == list:
        data = pd.DataFrame({"nv": [0] * len(seconds), "sec": seconds})
    if not SIMPLE:
        data = generate_features(LAT=LAT, LON=LON, data=data, year=year, month=month, day=day)
    data = generate_time_features(data)
    # time categories: hour, minutes
    categories = [
        np.array(list(range(-1, 24))),
        np.array(list(range(60))),
    ]
    ohe = OneHotEncoder(categories=categories)
    # Make y, X
    X = np.hstack(
        [
            data.drop(columns="nv").to_numpy(),
            ohe.fit_transform(data[["hour", "minute"]]).todense(),
        ]
    )
    y = data.nv
    y = y.to_numpy()
    y_pred = model.predict(X)
    return y_pred
