# Copyright (c) Pankaj Pansari 
#
# This file is part of CodeInsight, which is licensed under the MIT License.
# See the LICENSE file for details.

"""Main call script for the CodeInsight evaluator.

This script runs the CodeInsight evaluator (Proposer, Aggregator, and Annotator)
on the given program assignment with respect to the parameters in the configuration file. 

Typical usage example:

    $ python assignment_evaluator.py
"""

import argparse
import pathlib
import shutil
import time

import tqdm

import aggregator_llm
import annotator_llm
import proposer_llm
import utils

def eval():
    """Runs the CodeInsight evaluator on the given program assignment with 
    respect to the parameters in the configuration file. Calls Proposer, Aggregator, 
    and Annotator in sequence for each parameter and writes results to text files.

    Args:
        None

    Returns:
        None
    """
    total_params = len(utils.CONFIG['parameters'])
    total_models = len(utils.CONFIG['proposers']['models'])

    for param_index, parameter in enumerate(tqdm.tqdm(utils.CONFIG['parameters'])):
        print(f"\nProcessing parameter ({param_index + 1}/{total_params}) : {parameter['name']}")

        for model_index, model in enumerate(utils.CONFIG['proposers']['models']):
            if model_index == 0:
                print(f"Running Proposer on {model['type']} ({model_index + 1}/{total_models})")
            else:
                print(f"                 on {model['type']} ({model_index + 1}/{total_models})")
            proposer = proposer_llm.ProposerLLM(model, parameter)
            proposer.run()

        print("Running Aggregator")
        aggregator = aggregator_llm.AggregatorLLM(utils.CONFIG['aggregator']['model'], parameter)
        aggregator.run()

        print("Running Annotator")
        annotator = annotator_llm.AnnotatorLLM(utils.CONFIG['annotator']['model'], parameter)
        annotator.run()

        src = pathlib.Path(annotator.output_path) / pathlib.Path(annotator.output_filename)
        dest = (
            pathlib.Path(utils.CONFIG['assignment']['output_path']) /
            f"{utils.CONFIG['assignment']['problem_file'].split('/')[1].split('.')[0]}"
            f"_annotator_{utils.CONFIG['annotator']['model']['type']}.txt"
        )
        shutil.copyfile(src, dest)    

        print(f"\nParameter {parameter['name']} completed ({param_index + 1}/{total_params})\n")

    utils.parse_output(utils.CONFIG)
    print("\nAll parameters processed. Evaluation complete.")

if __name__ == '__main__':
    start_time = time.time()

    # Let's read the problem and solution files from the command line arguments
    parser = argparse.ArgumentParser(
        prog='assignment_evaluator.py',
        description='Run the CodeInsight evaluator on the given program assignment.')
    parser.add_argument('problem_file', type = str, help=f'Path to the problem file.')
    parser.add_argument('solution_file', type = str, help=f'Path to the program'
                        f'file to be annotated.')
    args = parser.parse_args()
    utils.CONFIG['assignment']['problem_file'] = args.problem_file
    utils.CONFIG['assignment']['solution_file'] = args.solution_file

    eval()

    end_time = time.time()

    print(f"\nTotal execution time: {end_time - start_time:.2f} seconds")