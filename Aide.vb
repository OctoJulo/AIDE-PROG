''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'''									Aide en VB								 '''
''' 						quelques formules simples						 '''
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
''' 	équivalence:
Cells(3, 8) = Range("C8") '
	
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'''		Les Variables
'	Crée une variable de chaine
    Dim variable As String
'	Affecte dans une variable la valeur d'une case
    Variable = Worksheets("nompage").Range("A1")
'	Affecte dans une variable une valeur
    Variable = "Valeurdelavariable"
'	Affecte dans une variable la valeur de la cellule Active
	Variable = ActiveCell.Value
'	regroupe les deux chaines de caractère  
    Chemin = Racine + Carte


''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''	
'''		Les plages:	
'	Crée une variable de plage
	Dim Plage As Range
'	Affecte cette variable à un plage 
    Set Plage = Worksheets("nompage").Range(Cells(2, 7), Cells(14, 12))
'	Affecte cette variable à un plage (seconde methode)
    Set Plage = Worksheets("nompage").Range("A3:A204,D3:D204")




	
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'''						Les manipulations de donnée.						 '''
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'''		La copie:
'	Copie la selection
    Selection.Copy
' 	Copie par case
    Sheets("nompage1").Range("A1").Copy Sheets("nompage2").Range("B3")
'	Copie par range
	Sheets("nompage1").Range("A1:C8").Copy Sheets("nompage2").Range("B3")
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''	
'''		La selection:

'	Selectionne la case active.
    ActiveCell.Select
'	Selectionne une case
    Range("A1").Select
'	Selectionne une matrice
    Range("A1836:D1836").Select
'	Selectionne la ligne 1
	Rows(1).Select
'	Selectionne les lignes 1 à 3	
	Rows("1:3").Select
' 	Selectionne la colonne 1
	Columns(1).Select
'	Selectionne les colonne A jusqu'a C
	Columns("A:C").Select
'	Selectionne toutes les cases.
    Cells.Select

'	Selectionne les données presente dans la plage.
    Selection.ClearContents
'	selection la derniere case non vide
    Selection.End(xlUp).Select
'	Selectionne la derniere cellule non vide du tableau
    [A65536].End(3).Select

	
'	Selectionne la derniere case non vide
    ActiveCell.SpecialCells(xlLastCell).Select
'	Fait un décalage de cellule active de 6 colonnes et de 2 lignes
    ActiveCell.Offset(2, 6).Range("A1").Select
 '	Selectionne toute la colonne A
    ActiveCell.Columns("A:A").EntireColumn.Select	
	
'	Remplie la case par le texte
    ActiveCell.FormulaR1C1 = "donnée a mettre dans la cellule"	
'	Copie dans la feuille active
    ActiveSheet.Paste
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'''		Les manipulations de page.
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

	Set FeuilleListe = Sheets("Liste")
'	Selection d'une page
    Sheets("sheet1").Select
    Sheets(nompage).Select
	
'	Renomme une page
    Sheets("sheet1").Name = "NouveauNom"
	
'	Suprimer une feuille(active)
    ActiveWindow.SelectedSheets.Delete

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''	
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''	
'''							FONCTIONS DIVERSES								 '''
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'fonction de recherche:
    Cells.Find(What:="motrecherché", After:=ActiveCell, LookIn:=xlFormulas, LookAt _
        :=xlPart, SearchOrder:=xlByRows, SearchDirection:=xlNext, MatchCase:= _
        False, SearchFormat:=False).Activate


''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''	
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''	
'''									LES PLUS								 '''
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
''' 	à placer en début de programme pour optimiser le temps de traitement
'	Cache la fenetre Excel
	ThisWorkbook.Application.Visible = False
'	Désactive la mise à jour de l'affichage
	Application.ScreenUpdating = False
'	Désactive la mise à jour des recalculs
	Application.Calculation = xlCalculationManual
''' 	à placer en fin de programme pour optimiser le temps de traitement	
'	Raffiche la fenetre Excel
	ThisWorkbook.Application.Visible = True
'	Ré-activations de la MAJ affichage
	Application.ScreenUpdating = True
'	Ré-activations des calculs automatique
	Application.Calculation = xlCalculationAutomatic
	
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''	
'''		Shell
'	Ouvre un explorateur Windobs avec comme chemin: Chemin
    Shell "explorer.exe /e,""" & Chemin & """", vbMaximizedFocus
'	Declaration d'un objet Shell
    Set objShell = CreateObject("Shell.Application")
'	Ouvre une fenetre de selection de dossier.
    Set objFolder = objShell.BrowseForFolder(&H0&, "Choisir un répertoire", &H1&)
'	Ouvre une fenetre de selection de fichier(arborescence)
 '	Ou ouvre directement le fichier selectionné
	Application.Dialogs(xlDialogOpen).Show ("c:\mes documents") 
	Application.Dialogs(xlDialogOpen).Show ("c:\mes documents\fichier.xls")	
'	Ouvre une fenetre de selection de fichier	
	résultatOK = Application.Dialogs(xlDialogOpen).Show 
'	Boucle tant qu'un fichier n'est pas selectionné
	If Not résultatOK Then 
		MsgBox "vous devez choisir un fichier" 
		GoTo encore 
	End If 
'	Retourne dans la variable le chemin du fichier, sans l'ouvrir
	Variablefichier = Application.GetOpenFilename 
	
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''	
'	Sauvegarde le document
    ActiveWorkbook.Save
    ActiveWorkbook.SaveAs Filename:= _
        "C:\Users\julesb\Desktop\TRAVAIL\MEMTEST\scenarioX.xlsx", FileFormat:= _
        xlOpenXMLWorkbook, CreateBackup:=False		
	
'	Décharge le Userform,(ferme la fenetre)
    Unload UserForm1	

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
    
'	Fait descendre le scroll dans la feuille ouverte.
    ActiveWindow.LargeScroll Down:=-1