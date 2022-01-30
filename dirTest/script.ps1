$fso = New-Object -com "Scripting.FileSystemObject"
$folder = $fso.GetFolder("C:\Users\Talita Halboth\Documents\GitHub\reposFromGraduation")

foreach ($subfolder in $folder.SubFolders)
{
    foreach ($subsubfolder in $subfolder.SubFolders)
    {
        If ($subsubfolder.Name -like ".git")
        {
            echo $subsubfolder.Path
            # get-childitem $subsubfolder.Path -recurse | remove-item
            rm -Force -Recurse $subsubfolder.Path
            # cat $subfolder.Path
            # remove-item $subsubfolder.Path -Verbose
        }       
    }
    # echo $subfolder.Name
    # If ($subfolder.Name -like "*UMARQUIVOTESTE")
    # {
        
    #     # cat $subfolder.Path
    #     remove-item $subfolder.Path -Verbose
    # }       
}