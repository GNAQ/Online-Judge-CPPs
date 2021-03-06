#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <cmath>
using namespace std;

struct splay_tree
{
    int fa, ch[2], valu, siz, w;
} tree[100010];
int tsiz = 0, troo = 0;
int opt, typ, val;

inline void readx(int &x)
{
    x = 0;
    int k = 1;
    register char ch = 0;
    while (ch < '0' || ch > '9')
    {
        ch = getchar();
        if (ch == '-')
            k = -1;
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    x *= k;
}

inline void updata(int pos)
{
    tree[pos].siz = tree[pos].w + tree[tree[pos].ch[0]].siz + tree[tree[pos].ch[1]].siz;
}
inline void rotatex(int inx)
{
    int f = tree[inx].fa, g = tree[f].fa, flag = (tree[f].ch[1] == inx), flag2 = (tree[g].ch[1] == f);

    tree[f].ch[flag] = tree[inx].ch[!flag];
    tree[f].fa = inx;
    if (tree[inx].ch[!flag])
        tree[tree[inx].ch[!flag]].fa = f;
    tree[inx].fa = g;
    tree[inx].ch[!flag] = f;
    if (g)
        tree[g].ch[flag2] = inx;

    updata(f);
    updata(inx);
}
inline void splay(int pos, int targ)
{
    for (; tree[pos].fa != targ; rotatex(pos))
    {
        if (tree[tree[pos].fa].fa != targ)
        {
            int g = tree[tree[pos].fa].fa;
            if ((tree[g].ch[1] == tree[pos].fa) == (tree[tree[pos].fa].ch[1] == pos))
                rotatex(tree[pos].fa);
            else
                rotatex(pos);
        }
    }
    if (!targ)
        troo = pos;
}

inline int splay_rank(int pos)
{
    if (tree[pos].valu == val)
    {
        splay(pos, 0);
        return tree[tree[pos].ch[0]].siz + 1;
    }
    else if (tree[pos].valu > val)
        return splay_rank(tree[pos].ch[0]);
    else
        return splay_rank(tree[pos].ch[1]);
}
inline int splay_val(int pos)
{
    if (tree[tree[pos].ch[0]].siz < val && tree[pos].w + tree[tree[pos].ch[0]].siz >= val)
    {
        splay(pos, 0);
        return tree[pos].valu;
    }
    else if (tree[tree[pos].ch[0]].siz >= val)
        return splay_val(tree[pos].ch[0]);
    else
    {
        val -= tree[tree[pos].ch[0]].siz + tree[pos].w;
        return splay_val(tree[pos].ch[1]);
    }
}
inline int splay_get_pos(int pos)
{
    if (tree[pos].valu == val)
        return pos;
    else if (tree[pos].valu < val)
        return splay_get_pos(tree[pos].ch[1]);
    else
        return splay_get_pos(tree[pos].ch[0]);
}
inline int splay_fb(int pos, int mode)
{
    pos = tree[pos].ch[mode];
    while (tree[pos].ch[mode ^ 1])
        pos = tree[pos].ch[mode ^ 1];
    return pos;
}

inline void splay_ins(int &inx, int f)
{
    if (!inx)
    {
        inx = ++tsiz;
        tree[inx].fa = f;
        tree[inx].siz = tree[inx].w = 1;
        tree[inx].valu = val;
        splay(inx, 0);
        return;
    }
    tree[inx].siz++;
    if (tree[inx].valu == val)
    {
        tree[inx].w++;
        splay(inx, 0);
        return;
    }
    splay_ins(tree[inx].ch[(tree[inx].valu < val)], inx);
    return;
}

inline void splay_del()
{
    int pos = splay_get_pos(troo);
    splay(pos, 0);
    if (tree[pos].w > 1)
    {
        tree[pos].w--;
        tree[pos].siz--;
        return;
    }
    if (tree[pos].siz == 1)
    {
        troo = -1;
        return;
    }
    if (!(tree[pos].ch[0] * tree[pos].ch[1]))
    {
        troo = tree[pos].ch[0] + tree[pos].ch[1];
        tree[troo].fa = 0;
        return;
    }
    splay(splay_fb(pos, 0), pos);
    troo = tree[pos].ch[0];
    tree[troo].fa = 0;
    tree[troo].ch[1] = tree[pos].ch[1];
    tree[tree[pos].ch[1]].fa = troo;
    updata(troo);
}

int main()
{
    tree[1].ch[0] = 2;
    tree[1].siz = 2;
    tree[1].w = 1;
    tree[1].valu = 2 * 1e9;
    tree[2].fa = 1;
    tree[2].siz = tree[2].w = 1;
    tree[2].valu = -2 * 1e9;
    tsiz = 2;
    troo = 1;

    readx(opt);
    for (int i = 1; i <= opt; i++)
    {
        readx(typ);
        readx(val);
        if (typ == 1)
            splay_ins(troo, 0);
        else if (typ == 2)
            splay_del();
        else if (typ == 3)
            printf("%d\n", splay_rank(troo) - 1);
        else if (typ == 4)
        {
            val++;
            printf("%d\n", splay_val(troo));
        }
        else
        {
            splay_ins(troo, 0);
            printf("%d\n", tree[splay_fb(troo, (typ == 6))].valu);
            splay_del();
        }
    }
    return 0;
}
