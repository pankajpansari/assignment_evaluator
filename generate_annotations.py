import anthropic
import os
import re
import subprocess
from pathlib import Path

client = anthropic.Anthropic()

all_tasks = {}
p = re.compile('([\w\d]*)\.[cC]')
with open('data/testing/meta_data.txt', 'r') as f:
    for line in f:
        if p.match(line):
            prog_file = p.match(line).group(1)
            f.readline()
            prog_task = f.readline()
            all_tasks[prog_file] = prog_task

current_dir = Path('data/testing/C_programs_aman_arbaaz')
c_files = [f for f in os.listdir(current_dir) if f.endswith('.c')]

for file in c_files: 

    if (int(file.split('.')[0].split('_')[1]) <= 10):
        if (int(file.split('.')[0].split('_')[1]) == 1):
            continue
        print(file)
        prefix = p.match(file).group(1)
        
        program_task = all_tasks[prefix]

        # write program task to a temporary file
        with open(os.path.join(current_dir, file.split('.')[0] + '.txt'), 'w') as f:
            f.write(program_task)
        
        problem_path = os.path.normpath(os.path.join(current_dir, file.split('.')[0] + '.txt'))
        program_path = os.path.normpath(os.path.join(current_dir, file))
        command = ['python3', 'assignment_evaluator.py', problem_path, program_path]
        
        print(f"Running: {' '.join(command)}")

        subprocess.run(command, capture_output=True, text=True)
        
        # remove temporary file
        os.remove(os.path.join(current_dir, file.split('.')[0] + '.txt'))


