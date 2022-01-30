Command line instructions


Git global setup

git config --global user.name "thcf16"
git config --global user.email "thcf16@inf.ufpr.br"

Create a new repository

git clone git@gitlab.c3sl.ufpr.br:thcf16/VerificadorOrtograficoOficinaComp.git
cd VerificadorOrtograficoOficinaComp
touch README.md
git add README.md
git commit -m "add README"
git push -u origin master

Existing folder or Git repository

cd existing_folder
git init
git remote add origin git@gitlab.c3sl.ufpr.br:thcf16/VerificadorOrtograficoOficinaComp.git
git add .
git commit
git push -u origin master