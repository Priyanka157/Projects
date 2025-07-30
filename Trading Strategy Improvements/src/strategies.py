import numpy as np
import pandas as pd

def sma_crossover(df, short_window=20, long_window=50):
    df = df.copy()
    df['SMA_Short'] = df['Close'].rolling(window=short_window).mean()
    df['SMA_Long'] = df['Close'].rolling(window=long_window).mean()
    df['Signal'] = 0

    df.loc[df.index[short_window:], 'Signal'] = np.where(
        df.loc[df.index[short_window:], 'SMA_Short'] > df.loc[df.index[short_window:], 'SMA_Long'],
        1,
        -1
    )
    return df

