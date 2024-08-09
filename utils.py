# Copyright (c) 2024 Pankaj Pansari 
#
# This file is part of program annotator, which is licensed under the MIT License.
# See the LICENSE file for details.
import os
from pathlib import Path
import yaml

def load_config(config_path = 'config.yaml'):
    with open(config_path, 'r') as f:
        config = yaml.safe_load(f)

    # Replace environment variable placeholders
    _replace_env_vars(config)

    return config

def _replace_env_vars(config):
    for key, value in config.items():
        if isinstance(value, dict):
            _replace_env_vars(value)
        elif isinstance(value, str) and value.startswith('$'):
            env_var = value[2:-1]
            config[key] = os.getenv(env_var, '')

CONFIG = load_config()

def parse_output(config):
    annotated_program = ''
    src = Path(CONFIG['assignment']['output_path']) / f"{CONFIG['assignment']['problem_file'].split('/')[1].split('.')[0]}_annotator_{CONFIG['annotator']['model']['type']}.txt"
    with open(src, 'r') as f:
        flag = 0
        for line in f:
            if  line.startswith('<code>'):
                flag = 1
                continue
            elif line.startswith('</code>'):
                flag = 0
            if flag == 1:
                annotated_program += line
    
    dest = Path(CONFIG['assignment']['output_path']) / f"{CONFIG['assignment']['problem_file'].split('/')[1].split('.')[0]}.c"
    with open(dest, 'w') as f:
        f.write(annotated_program)

    explanation = '' 
    with open(src, 'r') as f:
        flag = 0
        for line in f:
            if  line.startswith('<explanation>'):
                flag = 1
                continue
            elif line.startswith('</explanation>'):
                flag = 0
            if flag == 1:
                explanation += line
    
    dest = Path(CONFIG['assignment']['output_path']) / f"{CONFIG['assignment']['problem_file'].split('/')[1].split('.')[0]}_explanation.txt"
    with open(dest, 'w') as f:
        f.write(explanation)

    os.remove(src)