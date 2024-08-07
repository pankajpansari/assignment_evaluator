from pathlib import Path
import shutil
import time

from tqdm import tqdm

from aggregator_llm import AggregatorLLM
from annotator_llm import AnnotatorLLM
from proposer_llm import ProposerLLM
from utils import CONFIG, parse_output

def eval():

    total_params = len(CONFIG['parameters'])
    total_models = len(CONFIG['proposers']['models'])

    for param_index, parameter in enumerate(tqdm(CONFIG['parameters'])):
        print(f"\nProcessing parameter ({param_index + 1}/{total_params}) : {parameter['name']}")

        for model_index, model in enumerate(CONFIG['proposers']['models']):
            if model_index == 0:
                print(f"Running Proposer on {model['type']} ({model_index + 1}/{total_models})")
            else:
                print(f"                 on {model['type']} ({model_index + 1}/{total_models})")
            proposer = ProposerLLM(model, parameter)
            proposer.run()

        print("Running Aggregator")
        aggregator = AggregatorLLM(CONFIG['aggregator']['model'], parameter)
        aggregator.run()

        print("Running Annotator")
        annotator = AnnotatorLLM(CONFIG['annotator']['model'], parameter)
        annotator.run()

        src = Path(annotator.output_path) / Path(annotator.output_filename)
        dest = Path(CONFIG['assignment']['output_path']) / f"{CONFIG['assignment']['problem_file'].split('/')[1].split('.')[0]}_annotator_{CONFIG['annotator']['model']['type']}.txt"
        shutil.copyfile(src, dest)    

        print(f"\nParameter {parameter['name']} completed ({param_index + 1}/{total_params})\n")

    parse_output(CONFIG)
    print("\nAll parameters processed. Evaluation complete.")

if __name__ == '__main__':
    start_time = time.time()
    eval()
    end_time = time.time()
    print(f"\nTotal execution time: {end_time - start_time:.2f} seconds")