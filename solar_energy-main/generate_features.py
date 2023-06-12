from datetime import datetime, timedelta

import ephem
import numpy as np
import pandas as pd

def apply_time_features(x:int, i:int):
    """
    i=0 => hour
    i=1 => minute
    i=2 => second
    """
    y = timedelta(seconds=x) 
    data_string = str(y).split(":")
    if len(data_string) > i:
        try:
            d = int(data_string[i])
        except ValueError:
            d = -1
        return d
    else:
        return np.nan

def generate_time_features(data:pd.DataFrame):
    data["sec2"] = data["sec"] ** 2
    data["sec5"] = data["sec"] ** 0.5
    data["hour"] = data["sec"].apply(apply_time_features, i=0)
    data["minute"] = data["sec"].apply(apply_time_features, i=1)
    data["second"] = data["sec"].apply(apply_time_features, i=2)
    return data

def generate_features(LAT:float, LON:float, data:pd.DataFrame, year:int, month:int, day:int):
    ### Ephem
    observer = ephem.Observer()
    observer.lat = LAT
    observer.lon = LON
    observer.date = datetime(year=year, month=month, day=day)
    sun = ephem.Sun(observer)
    ## generate fuatures
    features = ["hlon", "hlat", "earth_distance", "radius", "mag", "a_dec", "a_ra"]
    for i in features:
        data[i] = np.nan
    for i, row in enumerate(data.iterrows()):
        sun.compute(observer.date.datetime() + timedelta(seconds=int(data.sec[i])))
        for feature in features:
            data.loc[i, feature] = sun.__getattribute__(feature)
    data = generate_time_features(data)
    return data

    