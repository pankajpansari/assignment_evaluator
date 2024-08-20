# Copyright (c) 2024 Pankaj Pansari 
#
# This file is part of CodeInsight, which is licensed under the MIT License.
# See the LICENSE file for details.
"""AnnotatorLLM class generates feedback annotations in program and a summary explanation. 

This class is used for the third and final stage of the evaluation. The output of the aggregator
is used to pin-point in the code the positive/negative aspects of implementation. A short explanation
summary of the feedback is also generated.

Typical usage example:
    
        import annotator_llm
        annotator = annotator_llm.AnnotatorLLM(model)
        annotator.run()
"""

import os
import pathlib

import base_llm
import utils

class AnnotatorLLM(base_llm.BaseLLM):
    """ Extends BaseLLM class to implement AnnotatorLLM class.

    Creates custom prompt to annotate the input program file based on aggregated 
    feedback obtained from aggregator. The user prompt includes the problem statement,
    the program solution, and the aggregated feedback. The system prompt tells exactly
    what the model is expected to do. The output is saved in an intermediate log file.
    
    Attributes:
        system_prompt_path: A string containing the path to file describing 
            what the annotator is expected to do.
        output_path: A string listing the directory where the annotated result is saved.
        output_filename: A string giving the filename of result. The filename indicates
            the program name (being evaluated).
    """
    def __init__(self, model):
        """ Initializes the instance based on CONFIG settings; also sets which
        LLM acts as annotator (derived from parent).
        
        Args:
            model: A dictionary containing the model name (eg. claude-3-haiku-20240307)
                and type (eg. claude)
        
        Returns:
            None
        """
        super().__init__(model, {'name': "", 'prompt_file': ""})
        self.system_prompt_path = f"{utils.CONFIG['annotator']['system_prompt']}" 
        output_prefix = (
            utils.CONFIG['assignment']['problem_file']
            .split('/')[-1].split('.')[0]
        )
        self.output_path = utils.CONFIG['assignment']['intermediate_path']
        if not os.path.exists(self.output_path):
            os.makedirs(self.output_path)
        self.output_filename = (f"{output_prefix}_annotator_"
                                f"{model['type']}.txt")

    def create_message_content(self):
        """ Creates the user prompt to be used for the annotator LLM. The prompt
        includes the problem statement, the program solution, and the aggregated
        feedback from the aggregator. System prompt asks the model to respond with
        <code> and <explanation> tags. This helps in parsing the output and saving
        the annotated program and explanation in separate files.
        
        Args:
            None

        Returns:
            A string containing the user prompt to be used for the annotator LLM.
        """
        problem_statement = self.read_file(self.problem_path)
        program_solution = self.read_file(self.program_path)
        output_prefix = utils.CONFIG['assignment']['problem_file'].split('/')[-1].split('.')[0]  
        aggregate_feedback = self.read_file(pathlib.Path(utils.CONFIG['assignment']['intermediate_path']) /
                                            (f"{output_prefix}_aggregator_"
                                             f"{utils.CONFIG['aggregator']['model']['type']}.txt"))

        return (f"<problem> {problem_statement} </problem> \n\n"
                f"<code> {program_solution} </code> \n\n"
                f"<data> {aggregate_feedback} </data> \n\n")
