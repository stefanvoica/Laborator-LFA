#include <bits/stdc++.h>
using namespace std;
ifstream fin ("input.txt");
ofstream fout ("output.txt");
map<pair<int, char>, vector<int>> mat;
unordered_map<int, vector<int>>lambda;
unordered_set <int> st_final;
unordered_map <int, unordered_set<int> > q; ///multimea de noduri in care pot ajunge plecand din starea q si aplicand 0 sau mai multe lambda-tranzitii
string cuv;

bool verifica (unordered_set<int> stare, int poz)
{
    if (poz == cuv.size())
    {
        unordered_set<int> stari_noi;
        for (int x : stare)
            for (int y : q[x])
                stari_noi.insert(y);
        for (auto x : stari_noi)
            if (st_final.find(x) != st_final.end())
                return 1;
        return 0;
    }
    unordered_set<int> stari_noi;
    ///lambda*
    for (int x : stare)
        for (int y : q[x])
        stari_noi.insert(y);
    ///litera
    unordered_set<int> stari_noi_lit;
    for (auto x : stari_noi)
        if (mat.find({x, cuv[poz]}) != mat.end())
            for (auto y : mat[ {x, cuv[poz]}])
                stari_noi_lit.insert(y);
    if (stari_noi_lit.empty())
        return 0;
    return verifica(stari_noi_lit, poz + 1);
}

void dfs_lambda (int x, unordered_set<int>& viz)
{
    viz.insert(x);
    for (auto y : lambda[x])
        if (viz.find(y) == viz.end())
            dfs_lambda(y, viz);
}

int main()
{
    int n, m, x, y, L, st_init, nrF, nrCuv;
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
        if (mat.find({x,l}) == mat.end())
            mat[ {x, l}] = {y};
        else mat[ {x,l}].push_back(y);
    }
    fin >> L;
    for (int i = 1; i <= L; i++)
    {
        fin >> x >> y;
        if (lambda.find(x) == lambda.end())
            lambda[x] = {y};
        else    lambda[x].push_back(y);
    }
    for (int i = 0; i < n; i++)
    {
        int nod = stari[i];
        unordered_set<int> viz;
        dfs_lambda(nod, viz);
        q[nod]=viz;
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
        if (verifica({st_init}, 0))
            fout << "DA";
        else fout << "NU";
        fout << '\n';
    }
    return 0;
}
