Tema 3 APD
    Nicolae Alexandru-Dimitrie,336CA

    Am incercat sa implementez doar primul exercitiu din aceasta tema,si anume afisarea topologiei de catre fiecare proces,de aceea
consider ca exista legatura dintre procesele master 0 si 1.
    Initial, am preluat din argumente numarul total de procese si am declarat numarul de workeri si un vector de workeri pe care ii 
voi citi din fiecare fisier pt fiecare proces master.De asemenea,am mai declarat si o matrice in care voi retinie pe linia corespunzatoare
fiecarui rank al unui proces de tip master,workerii acestuia.Aceasta matrice va fi trimisa intre procesele master si de procesele master catre
workerii lor.
    Apoi,deschid fiecare fisier cluster in functie de rankul pe care il am si imi formez matricea,trimitand-o intre procesele master,folosind 
functiile MPI_Send() si MPI_Recv().In plus,mai trimit si rankul proceselor master catre workerii acestora si afisez fiecare pereche de 
M(master,worker).
    Dupa aceea,am afisat folosind functia print_topology,care respecta formatul output-ului din cerinta,topologia pentru rank-ul 3 si am trimis
matricea catre procesul 0.Apoi,pentru celelalte rank-uri master,primesc matricea si afisez topologia pentru ei si trimit topologia workerilor
lor.In final,pentru rank-urile de tip worker afisez topologia.