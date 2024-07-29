from proposer_llm import ProposerLLM
from aggregator_llm import AggregatorLLM
from annotator_llm import AnnotatorLLM
from config_loader import CONFIG

def eval():

    for parameter in CONFIG['parameters']:
        for model in CONFIG['proposers']['models']:
            print(f"Running Proposer for {parameter['name']} on {model['name']}\n")
            proposer = ProposerLLM(model, parameter)
            proposer.run()

        print(f"Running Aggregator for {parameter['name']} on {CONFIG['aggregator']['model']['name']}\n")
        aggregator = AggregatorLLM(CONFIG['aggregator']['model'], parameter)
        aggregator.run()
        print(f"Done\n")

        print(f"Running Annotator for {parameter['name']} on {CONFIG['annotator']['model']['name']}\n")
        annotator = AnnotatorLLM(CONFIG['annotator']['model'], parameter)
        annotator.run()
        print(f"Done\n")

if __name__ == '__main__':
    eval()