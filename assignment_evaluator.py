from proposer_llm import ProposerLLM
from aggregator_llm import AggregatorLLM
from annotator_llm import AnnotatorLLM

def eval():

#    for model in [#'claude-3-5-sonnet-20240620',
#                  #'mistralai/Mixtral-8x22B-Instruct-v0.1',
#                  'meta-llama/Meta-Llama-3.1-405B-Instruct-Turbo',
#                  ]:
#        config = {
#            'model' : model,
#            'parameter' : 'efficiency',
#            'assignment_name' : 'cs61_pset0',
#        }
#        print(f"Running Proposer for {model}")
#        proposer = ProposerLLM(config)
#        print(f"...done\n")
#        proposer.run()
#
#    config = {'model' : 'claude-3-5-sonnet-20240620', 'parameter' : 'efficiency', 'assignment_name' : 'cs61_pset0'}
#    print(f"Running Aggregator")
#    aggregator = AggregatorLLM(config)
#    print(f"...done\n")
#    aggregator.run()
#
    config = {'model' : 'claude-3-5-sonnet-20240620', 'parameter' : 'efficiency', 'assignment_name' : 'cs61_pset0'}
    print(f"Running Annotator")
    annotator = AnnotatorLLM(config)
    print(f"...done\n")
    annotator.run()

if __name__ == '__main__':
    eval()