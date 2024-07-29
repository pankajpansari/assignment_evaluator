import yaml
import os
from pathlib import Path

def load_config(config_path: str = 'config.yaml') -> dict:
    with open(config_path, 'r') as f:
        config = yaml.safe_load(f)

    # Replace environment variable placeholders
    _replace_env_vars(config)

    return config

def _replace_env_vars(config: dict) -> None:
    for key, value in config.items():
        if isinstance(value, dict):
            _replace_env_vars(value)
        elif isinstance(value, str) and value.startswith('$'):
            env_var = value[2:-1]
            config[key] = os.getenv(env_var, '')

CONFIG = load_config()