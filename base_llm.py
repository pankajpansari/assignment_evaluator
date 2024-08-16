# Copyright (c) 2024 Pankaj Pansari 
#
# This file is part of program annotator, which is licensed under the MIT License.
# See the LICENSE file for details.
""" Module defines the BaseLLM class which is the base class for Proposer, Aggregator, and Annotator classes.

Typical usage example:

    import base_llm
    class DerivedLLM(base_llm.BaseLLM)
"""
import os
import pathlib

import anthropic
import openai
import together

import utils

class BaseLLM:
    """ Base class for Proposer, Aggregator, and Annotator classes.

    This class provides the common functionality for Proposer, Aggregator, 
    and Annotator classes such as reading files, creating message content for
    LLM API, getting model response, and writing output.

    Attributes:
        model: A dictionary containing the model name (eg. claude-3-haiku-20240307)
            and type (eg. claude)
        parameter: A dictionary containing the parameter name and the path to
            the respective prompt file which describes the parameter.
        problem_path: A string containing the path to the problem file. (from config file)
        solution_path: A string containing the path to the solution file. (from config file)
        output_path: A string listing the directory where the result is saved. (from config file)
    """
    def __init__(self, model, parameter):
        """ Provides the initialization method to set attributes for parent class.
        
        Args:
            model: A dictionary containing the model name (eg. claude-3-haiku-20240307)
                and type (eg. claude)
            parameter: A dictionary containing the parameter name and the path to
                the respective prompt file which describes the parameter.
        
        Returns:
            None
        """
        self.model = model
        self.parameter = parameter['name']
        self.problem_path = utils.CONFIG['assignment']['problem_file']
        self.solution_path = utils.CONFIG['assignment']['solution_file']
        self.output_path = utils.CONFIG['assignment']['output_path']
        os.makedirs(self.output_path, exist_ok=True)

    def get_client(self):
        """ Returns a client object by calling the appropriate class constructor.

        Args:
            None

        Returns:
            A client object based on the model name.
        """
        if self.model['name'].startswith('claude'):
            return anthropic.Anthropic()
        elif self.model['name'].startswith('gpt'):
            return openai.OpenAI()
        else:
            return together.Together() 


    def read_file(self, file_path):
        """ Reads the content of a file and returns it as a string.

        Args:
            file_path: A string containing the path to the file to be read.

        Returns:
            A string containing the content of the file.
        """
        with open(file_path, 'r') as f:
            return f.read()
    
    def create_message_content(self):
        """ Abstract method to be implemented by subclasses to create the user prompt.
        Raises an error if not implemented.

        Args:
            None
        
        Returns:
            NotImplementedError: An error if the method is not implemented.
        """
        raise NotImplementedError("Subclasses must implement this method")
    
    def get_model_response(self, client):
        """ Creates and returns an object of type Messages or ChatCompletion.
        To create the object, we pass the model name, system prompt, and user prompt.
        We obtain the response from the model by calling the create method.

        Args:
            client: A client object based on the model name.

        Returns:
            An object of type Messages or ChatCompletion containing the 
            response from the model.
        """
        system_prompt = self.read_file(self.system_prompt_path)
        message_content = self.create_message_content()

        if isinstance(client, anthropic.Anthropic):
            return client.messages.create(
                model = self.model['name'],
                max_tokens = 1000,
                temperature = 0.0,
                system = system_prompt,
                messages = [{"role": "user", "content": message_content}],
            )
        else:
            return client.chat.completions.create(
                model = self.model['name'], 
                messages = [ 
                    {"role": "system", "content": system_prompt},
                    {"role": "user", "content": message_content},
               ],
            )

    def write_output(self, response, output_filename):
        """ Writes the output to a file.

        Args:
            response: An object of type Messages or ChatCompletion containing 
            the response from the model.
            output_filename: A string containing the name of the output file.
        
        Returns:
            None
        """
        output_file = pathlib.Path(self.output_path) / output_filename 
        if isinstance(self.get_client(), anthropic.Anthropic):
            content = response.content[0].text
        else:
            content = response.choices[0].message.content

        os.makedirs(output_file.parent, exist_ok=True)
        with open(output_file, 'w', encoding = 'utf-8') as f:
            f.write(f"{self.model['name']}\n")
            f.write(f"{self.parameter}\n")
            f.write(content)

    def run(self):
        """ Calls class methods to get the client object, model response, 
        and write output to a file.
        
        Args:
            None

        Returns:
            None
        """
        client = self.get_client()
        response = self.get_model_response(client)
        self.write_output(response, self.output_filename)