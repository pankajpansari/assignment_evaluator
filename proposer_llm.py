# Copyright (c) 2024 Pankaj Pansari 
#
# This file is part of CodeInsight, which is licensed under the MIT License.
# See the LICENSE file for details.
""" ProposerLLM class calls given model for feedback on the given parameter.

This class is used for the first stage of the evaluation. We instantiate a ProposerLLM object
based on given model and evaluation parameters. There are multiple proposers in the first stage.

Typical usage example:
    
        import proposer_llm
        proposer = proposer_llm.ProposerLLM(model, parameter)
        proposer.run()
"""
import os
import pathlib

import base_llm
import utils

class ProposerLLM(base_llm.BaseLLM):
    """ Extends BaseLLM class to implement ProposerLLM class.
    
    Creates custom prompt to obtain initial feedback (proposals) from variety 
    of LLMs (given in config). The user prompt includes the problem statement, 
    the program solution, and the parameter being evaluated. The system prompt 
    tells exactly what the model is expected to do. The output is saved in an 
    intermediate log file. 

    Attributes:
        parameter_prompt_path: A string containing the path to file describing 
            the evaluation parameter.
        system_prompt_path: A string containing the path to file describing
            what the model is expected to do.
        output_path: A string listing the directory where the result is saved.
        output_filename: A string giving the filename of result. The filename indicates
            the program name (being evaluated) and the parameter name.
    """
    def __init__(self, model, parameter):
        """ Initializes the instance based on CONFIG settings; also based on
        LLM model name and parameter to be evaluated (these coming from parent class)
        
        Args:
            model: A dictionary containing the model name (eg. claude-3-haiku-20240307)
                and type (eg. claude)
            parameter: A dictionary containing the parameter name and the path to
                the respective prompt file which describes the parameter.
        
        Returns:
            None 
        """
        super().__init__(model, parameter)
        self.parameter_prompt_path = f"{parameter['prompt_file']}"
        self.system_prompt_path = f"{utils.CONFIG['proposers']['system_prompt']}"
        output_prefix = utils.CONFIG['assignment']['problem_file'].split('/')[1].split('.')[0]  
        self.output_path = utils.CONFIG['assignment']['intermediate_path']
        if not os.path.exists(self.output_path):
            os.makedirs(self.output_path)
        self.output_filename = (
            f"{output_prefix}_proposer_{model['type']}"
            f"_{parameter['name']}.txt"
        )

    def create_message_content(self):
        """ Creates the user prompt to be be used for the proposer LLM
        for this parameter evaluation. Prompt includes the problem statement,
        the program solution, and instructions about parameter eval. 
        
        Args:
            None
        
        Returns:
            A string containing the user prompt for the proposer LLM.
        """
        problem_statement = self.read_file(self.problem_path)
        program_solution = self.read_file(self.solution_path)
        parameter_prompt = self.read_file(self.parameter_prompt_path)

        return (f"<problem> {problem_statement} </problem> \n\n"
                f"<code> {program_solution} </code> \n\n"
                f"<instructions> {parameter_prompt} </instructions>")