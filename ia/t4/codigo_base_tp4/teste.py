import subprocess

command = "python frozen_lake.py -e 0.5 -tr 100 -s"
with open('myfile', "a") as outfile:
    # subprocess.run(command, stdout=outfile)
    process = subprocess.Popen(command, shell=False, stdout=outfile)

    process.wait()