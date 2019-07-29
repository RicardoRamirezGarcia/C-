@echo off 
setlocal ENABLEDELAYEDEXPANSION
	set i=1
	set a=1
	for %%S in  (GATournamentSelector GARouletteWheelSelector) do (
		for %%P in (100 150) do (  
			 for %%C in (0.8 0.85 0.9 0.95) do (
				 for %%M in (0.01 0.05 0.1 0.125 0.15) do (
					for %%T in (Caso-A4.txt)  do (
						echo !i! de 80
				 	  	Sudoku.exe %%T %%P %%S %%C %%M >> Caso4.txt
						set/a i=!i!+1
					) 
				)	
			)
		)
	)		