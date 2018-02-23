# Git Command line Usage

1. Create a new folder anywhere on your computer, for example, named "SunE_Bot"
2. Enter the "SunE_Bot" folder and initialize the folder: ```git init```
3. Add local repository to remote: ```git remote add origin https://github.com/cverd001/Senior-Design.git```
4. Download the newest version of codes: ```git pull origin master```
5. Add all changes in the working directory to the staging area: ```git add .```
6. Describe your updates: ```git commit -m "(your statements)"```
7. Upload codes to the server: ```git push origin master```

# Tips to avoiding conflicts
1. Check repository status under current branch using ```git status``` (MUST AFTER PULL)
2. Discard changes in working directory under current branch(master) using ``` git checkout master```
