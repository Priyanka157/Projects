import yfinance as yf
import pandas as pd

def get_data(ticker="SPY", start="2018-01-01", end="2024-12-31"):
    df = yf.download(ticker, start=start, end=end, auto_adjust=True)
    df = df[['Open', 'High', 'Low', 'Close', 'Volume']]
    df.dropna(inplace=True)
    return df
