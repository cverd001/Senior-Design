# Git Command line Usage

1. Create a new folder anywhere on your computer, for example, named "SunE_Bot"
2. Enter the "SunE_Bot" folder and initialize the folder: ```git init```
3. Add local repository to remote: ```git remote add origin https://github.com/cverd001/Senior-Design.git```
4. Download the newest version of codes: ```git pull origin master```
5. Add all changes in the working directory to the staging area: ```git add .```
6. Describe your updates: ```git commit -m "(your statements)"```
7. Upload codes to the server: ```git push origin master```

## Tips to Avoiding Conflicts
1. Check repository status under current branch using ```git status``` (MUST AFTER PULL)
2. Discard changes in working directory under current branch(master) using ``` git checkout master``` or using ```git stash``` to go back to the clean working directory

## Branches
1. The old versions are all in the branch "debug", using ```git checkout debug``` to switch to this branch
2. If you want to go back to master, using ```git checkout master```
3. Create a new branch: ```git checkout -b <NEW_BRANCH_NAME>```
