# Copyright (c) 2024 Pankaj Pansari 
#
# This file is part of CodeInsight, which is licensed under the MIT License.
# See the LICENSE file for details.
import os
from pathlib import Path
import yaml

def load_config(config_path = 'config.yaml'):
    """ Load the given configuration yaml file.

    Args:
        config_path: Path to the configuration file.
            Default is config.yaml in the current directory. 
    
    Returns:
        config: A dictionary containing the configuration settings.
    """
    with open(config_path, 'r') as f:
        config = yaml.safe_load(f)

    # Replace environment variable placeholders
    _replace_env_vars(config)

    return config

def _replace_env_vars(config):
    """ Replace environment variable placeholders in the configuration.
    These settings are used to store sensitive information such as API keys.

    Args:
        config: A dictionary containing the configuration settings.
    
    Returns:
        None
    """
    for key, value in config.items():
        if isinstance(value, dict):
            _replace_env_vars(value)
        elif isinstance(value, str) and value.startswith('$'):
            env_var = value[2:-1]
            config[key] = os.getenv(env_var, '')

CONFIG = load_config()

def parse_output(config):
    """ Parse the output of the annotator to extract the annotated program 
    file and explanation. The annotator was prompted to make use of <code> and 
    <explanation> tags in its output. Here we use those tags to parse and write 
    the annotated program and explanation to separate files.

    Args:
        config: A dictionary containing the configuration settings.

    Returns:
        None
    """
    annotated_program = ''
    src = Path(CONFIG['assignment']['output_path']) / f"{CONFIG['assignment']['problem_file'].split('/')[-1].split('.')[0]}_annotator_{CONFIG['annotator']['model']['type']}.txt"
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
    
    dest = Path(CONFIG['assignment']['output_path']) / f"{CONFIG['assignment']['problem_file'].split('/')[-1].split('.')[0]}.c"
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
    
    dest = Path(CONFIG['assignment']['output_path']) / f"{CONFIG['assignment']['problem_file'].split('/')[-1].split('.')[0]}_explanation.txt"
    with open(dest, 'w') as f:
        f.write(explanation)

    os.remove(src)