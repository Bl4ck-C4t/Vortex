%{

%}

%token TYPE SYMBOL

%%
calc: 
    | calc TYPE {cout << $1 << endl;}

%%