#include <bits/stdc++.h>
using namespace std;
ifstream fin ("input.txt");
ofstream fout ("output.txt");
map<pair<int, char>, int> mat;
unordered_set <int> st_final;
map<pair<int,int>, int> from;
string cuv;

void reconstituie (int y, int poz)
{
    if (poz == 0)
    {
        fout << from[{y,poz}] << ' ' << y << ' ';
        return;
    }
    reconstituie(from[{y,poz}], poz-1);
    fout<<y<<' ';
}

bool verifica (int stare, int poz)
{
    if (poz == cuv.size())
    {
        if (st_final.find(stare) == st_final.end())
            return 0;
        fout<<"Drumul :";
        reconstituie(stare, poz-1);
        fout<<'\n';
        return 1;
    }
    if (mat.find({stare, cuv[poz]}) == mat.end())
        return 0;
    from[{mat[{stare, cuv[poz]}],poz}] = stare;
    return verifica(mat[{stare, cuv[poz]}], poz + 1);
}

int main()
{
    int n, m, x, y, st_init, nrF, nrCuv;
    char l;
    vector<int>stari;
    fin >> n;
    for (int i = 1; i <= n; i++)
    {
        fin >> x;
        stari.push_back(x);
    }
    fin >> m;
    for (int i = 1; i <= m; i++)
    {
        fin >> x >> y >> l;
        mat[{x,l}]=y;
    }
    fin >> st_init >> nrF;
    for (int i = 1; i <= nrF; i++)
    {
        fin >> x;
        st_final.insert(x);
    }
    fin >> nrCuv;
    for (int i = 1; i <= nrCuv; i++)
    {
        fin >> cuv;
        if (verifica(st_init, 0))
            fout << "DA";
        else fout<<"NU";
        fout << '\n';
        from.clear();
    }
}

