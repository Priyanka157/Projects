import numpy as np

def sharpe_ratio(df, strategy_col='Strategy', risk_free_rate=0.0):
    """
    Compute annualized Sharpe Ratio from strategy returns.
    Assumes daily data (252 trading days).
    """
    returns = df[strategy_col].dropna()

    # Avoid divide-by-zero
    if returns.std() == 0 or returns.empty:
        return float('nan')

    excess_returns = returns - risk_free_rate / 252
    sharpe = (excess_returns.mean() / excess_returns.std()) * (252 ** 0.5)
    return sharpe


def max_drawdown(df, equity_col='Equity'):
    """
    Compute the maximum drawdown from equity curve.
    """
    equity = df[equity_col].dropna()

    if equity.empty:
        return float('nan')

    rolling_max = equity.cummax()
    drawdown = (equity - rolling_max) / rolling_max
    return drawdown.min()

