def backtest(df, signal_col='Signal'):
    df = df.copy()
    df['Strategy'] = df[signal_col].shift(1) * df['Returns']
    df['Equity'] = (1 + df['Strategy']).cumprod()
    return df

