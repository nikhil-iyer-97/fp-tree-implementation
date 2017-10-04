#include <bits/stdc++.h>

#define pb push_back
#define ld long double
#define ll long long
#define mp make_pair

using namespace std;

ld minconf=0.9;

ofstream output_file2;

struct frequent
{
    vector<ll> v;
    ll cnt;
};

struct node
{
	map<ll,struct node*> m;
	ll counter;
	ll value;
	ll flag;
	ll pole;
	struct node *parent,*l;
};

struct tree
{
	node* node_links[60];
	node *root_tree;
};

vector <struct frequent> arr[10];

ll sup_cnt =400;
ll mdata[]={4,4,4,4,8,4,8,4};

string str[]={"pregnant1","pregnant2","pregnant3","pregnant4"
,"PGC1","PGC2","PGC3","PGC4"
,"BP1","BP2","BP3","BP4",
"Triceps1","Triceps2","Triceps3"
,"insulin1","insulin2","insulin3","insulin4",
"insulin5","insulin6","insulin7","insulin8",
"BM1","BM2","BM3","BM4","Dia_pedigree1","Dia_pedigree2","Dia_pedigree3","Dia_pedigree4","Dia_pedigree5",
"Dia_pedigree6","Dia_pedigree7","Dia_pedigree8","Dia_pedigree9"
,"Dia_pedigree10","Dia_pedigree11","Dia_pedigree12",
"Age1","Age2","Age3","Age4",
"no_diabeties","diabeties"};

string str2[46] ;
vector<ll> data1[768];
ld data[768][9];
ll itemcount[50];

vector<ll> split(ll lo,ll hi,ll num,ll count,vector <pair<ld,ld> > arr)
{
    ll i,upcount1=0,upcount0=0,mid=-1,tot=hi-lo+1,fcount;
    ld p=(ld)(count)/(ld) (tot);
    ld entro=-(p*log2f(p))-((1-p)*log2f(1-p)),tentro;
    vector<ll> l,r;
    for(i=lo;i<hi;i++)
    {
        if(arr[i].second==1.0)
        {
            upcount1++;
        }
        p=(ld)(upcount1)/(ld)(i-lo+1);
        tentro=-(p*log2f(p))-((1.0-p)*log2f(1-p));
        tentro=((ld)(i-lo+1)/(ld)(tot))*tentro;
        p=((ld)(count-upcount1))/(ld)(hi-i);
        tentro+=((ld)(hi-i)/(ld)(tot))*(-(p*log2f(p))-((1.0-p)*log2f(1.0-p)));
        if(entro-tentro>0.0)
        {
            mid=i;
            entro=tentro;
            fcount=upcount1;
        }
    }
    if(num-2>0 && mid!=-1)
    {
        if(mid>lo+2 && fcount>0 && (mid-lo+1)-fcount>0)
            l=split(lo,mid,num-2,fcount,arr);
        if(hi>mid+2 && count-fcount>0 && hi-mid-(count-fcount)>0)
            r=split(mid+1,hi,num-2,count-fcount,arr);
    }
    if(mid==-1)
    {
        return l;
    }
    l.pb(mid);
    l.insert(l.end(),r.begin(),r.end());
    return l;
}
void get_data()
{
	//ll data[495][17];
	ifstream file("input.txt");
	string line;
	for(ll j=0;j<768;j++)
	{
	    ll count=0;
	 	getline(file,line);
		istringstream strstream(line);
		string item;
		for(ll i=0;i<9;i++)

		{
			getline(strstream,item,',');
			char *a = const_cast <char*>(item.c_str());
            if(i==0 || i==8)
                data[j][i]=(ld)(atoi(a));
            else
                data[j][i]=(ld)(atof(a));
            if(i!=0 && i!=8 && (data[j][i]==0.0 || data[j][i]==0))
            {
                data[j][i]=-500.0;
            }
        }
	}
}

void splitting(vector<ld> d_pnts,ll i,ll num)
{
    ll j,temp;
    ll r=0;
    for(j=0;j<768;j++)
    {
        if(data[j][i]!=-500.0)
        {
            for(r=0;r<d_pnts.size();r++)
            {
                if(data[j][i]<=d_pnts[r])
                    break;
            }
            temp=r;
            temp++;
            data1[j].pb(num-temp);
        }
    }
}

void get_val(ll sz)
{
    ll i=0,j;
    pair<ll,ll> parr[60];
    map<ll,ll> mp;
    for(j=0;j<768;j++)
    {
        for(i=0;i<data1[j].size();i++)
        {
            parr[-data1[j][i]].first++;
            parr[-data1[j][i]].second=data1[j][i];
        }

    }
    sort(parr+1,parr+sz+1);
    for(i=sz,j=1;i>=1;i--,j++)
    {
        itemcount[j]=parr[i].first;
        mp[parr[i].second]=j;
        str2[j]=str[-parr[i].second-1];
    }
    for(j=0;j<768;j++)
    {
        for(i=0;i<data1[j].size();i++)
        {
            data1[j][i]=mp[data1[j][i]];
        }
    }
}
void preprocessing()
{
    ll i,j,r=0,count1=0,count2=0,sz=0;
    vector<ll> s_pnts;
    vector<pair<ld,ld> > temp;
    vector <ld> d_pnts;
    get_data();
    for(j=0;j<768;j++)
    {
        if(data[j][8]==1.0)
        {
            count1++;
        }
    }
    for(i=0;i<8;i++)
    {
        for(j=0;j<768;j++)
        {
            if(data[j][i]!=-500)
                temp.pb(mp(data[j][i],data[j][8]));
        }
        sort(temp.begin(),temp.end());
        s_pnts=split(0,temp.size()-1,mdata[i],count1,temp);
        for(r=0;r<s_pnts.size();r++)
        {
                d_pnts.pb(temp[s_pnts[r]].first);
        }
        splitting(d_pnts,i,count2);
        count2=count2-s_pnts.size()-1;
        sz+=s_pnts.size()+1;
        s_pnts.clear();
        d_pnts.clear();
        temp.clear();
    }
    d_pnts.pb(0);
    d_pnts.pb(1);
    splitting(d_pnts,8,count2);
    get_val(sz+2);
}

node* copyfnc(node* actroot,node* root,node* node_links[])
{

	node *temp = root;
	node *nroot = new node();
	map<ll,struct node*>::iterator it;
	nroot->parent = actroot;
	nroot->value = temp->value;
	nroot->flag=0;
	nroot->pole=0;
	nroot->counter = temp->counter;
	nroot->l=node_links[nroot->value];
	node_links[nroot->value]=nroot;
	for(it=temp->m.begin();it!=temp->m.end();it++)
	{
		nroot->m[it->first] = copyfnc(nroot,temp->m[it->first],node_links);
	}
	return nroot;
}
ll traverse(node* root,ll item_count[],ll k)
{
    vector<ll> ra;
    node *temp = root;
    if(temp->value==k)
    {
        temp->m.clear();
        return temp->counter;
    }
    map<ll,struct node*>::iterator it;
    temp->counter=0;
    for(it=temp->m.begin();it!=temp->m.end();it++)
    {

        if(it->second->flag==0)
        {
             ra.pb(it->first);
        }
        else
        {
            temp->counter+= traverse(temp->m[it->first],item_count,k);
            item_count[temp->value] += temp->counter;
        }
    }
    for(ll i=0;i<ra.size();i++)
    {
        temp->m.erase(ra[i]);
    }
    return temp->counter;
}
void traverse1(node *root,ll item_count[])
{
    map<ll,struct node*>::iterator it;
    for(it=root->m.begin();it!=root->m.end();it++)
    {
        ll val = root->m[it->first]->value;
        if(item_count[val]<sup_cnt)
            root->m[it->first]->pole = -1;
        traverse1(root->m[it->first],item_count);
    }
    return;
}
void make_set_from_node(node *root,list<pair<ll,ll>> l)
{
    ll sz = l.size();
    frequent titem;
    titem.cnt = l.front().first;
    list<pair<ll,ll>>:: iterator it1;
    for(it1=l.begin();it1!=l.end();it1++)
    {
        titem.v.pb(it1->second);
    }
    arr[sz].pb(titem);
	tree t1;
	for(ll i=0;i<60;i++)
		t1.node_links[i]=NULL;
	t1.root_tree = copyfnc(NULL,root,t1.node_links);
	ll k = l.front().second;
	node *temp=t1.node_links[k];
	while(temp!=NULL)
    {
        node *temp1 = temp;
        while(temp1->value!=0)
        {
            temp1->flag=1;
            temp1 = temp1->parent;
        }
        temp = temp->l;
    }
	ll item_count[60];

    memset(item_count,0,sizeof(item_count));

    traverse(t1.root_tree,item_count,k);

    traverse1(t1.root_tree,item_count);

    for(ll i=1;i<60;i++)
    {
        if(item_count[i]>sup_cnt)
        {
            l.push_front({item_count[i],i});
            make_set_from_node(t1.root_tree,l);
            l.pop_front();
        }
    }
}

void make_rule_i(vector <ll> l1,vector<ll> r1,ll right,ll i,ll k)
{
    ll j;
    vector<ll> l2;
    ld count;
    if(right>=k-1)
    {
        for(ll r=0;r<arr[k-right].size();r++)
        {
            if(l1==arr[k-right][r].v)
            {
                count=(ld)(arr[k-right][r].cnt);
                break;
            }

        }
        if((ld)(arr[k][i].cnt)/count>minconf)
        {
            output_file2<<"{";
            for(j=0;j<l1.size();j++)
            {
                output_file2<<str2[l1[j]]<<" ,";
            }
            output_file2<<"}"<<count<<"=>{";
            for(j=0;j<r1.size();j++)
            {
                output_file2<<str2[r1[j]]<<" ,";
            }
            output_file2<<"}";
            output_file2<<"\n";
            return;
        }
        else
        {
                return;
        }
    }
    else
    {
        if(right>0)
        {
            for(ll r=0;r<arr[k-right].size();r++)
            {
                if(l1==arr[k-right][r].v)
                {
                    count=arr[k-right][r].cnt;
                    break;
                }
            }
            if((ld)(arr[k][i].cnt)/count>minconf)
            {
                output_file2<<"{";
                for(j=0;j<l1.size();j++)
                {
                        output_file2<<str2[l1[j]]<<" ,";
                }
                output_file2<<"}"<<count<<"=>{";
                for(j=0;j<r1.size();j++)
                {
                        output_file2<<str2[r1[j]]<<" ,";
                }
                output_file2<<"}";
                output_file2<<"\n";
            }
            else
            {
                return ;
            }
        }
        for(j=0;j<l1.size();j++)
        {
            for(ll r=0;r<l1.size();r++)
            {
                if(r==j)
                    continue;
                else
                    l2.pb(l1[r]);
            }
            if(right==0 || l1[j]>r1[r1.size()-1])
            {
                r1.pb(l1[j]);
                make_rule_i(l2,r1,right+1,i,k);
                r1.pop_back();
            }
            l2.clear();
        }
    }
}
void rule_generate(ll k)
{
    ll i=0,j=0;
    vector <ll> left1;
    vector <ll> right1;
    for(i=0;i<arr[k].size();i++)
    {
        left1=arr[k][i].v;
        make_rule_i(left1,right1,0,i,k);
    }
}
int main()
{
    output_file2.open("out2.txt");
	ll tot_items = 45;
	preprocessing();
	tree t ;
	for(ll i=0;i<60;i++)

		t.node_links[i]=NULL;
	t.root_tree = new node();

	t.root_tree->value = 0;
	map<ll,struct node*>::iterator it;
	for(ll i=0;i<768;i++)
	{
		node *temp = t.root_tree;
		sort(data1[i].begin(),data1[i].end());
		for(ll j=0;j<data1[i].size();j++)
		{
			if(itemcount[data1[i][j]]>sup_cnt)
			{
                ll k = data1[i][j];
                it = temp->m.find(k);
                if(it==temp->m.end())
                {
                    temp->m[k] = new node();
                    temp->m[k]->parent = temp;
                    temp->m[k]->value = k;
                    temp->m[k]->counter = 1;
                    temp->m[k]->flag=0;
                    temp->m[k]->pole=0;
                    temp->l = t.node_links[k];
                    t.node_links[k] = temp;
                }
                else
                {
                    temp->m[k]->counter++;
                }
                temp=temp->m[k];
            }

        }
	}
	vector <ll> tj;
	for(ll i = tot_items;i>0;i--)
	{
		if(itemcount[i]>sup_cnt)
		{
			list<pair<ll,ll>> l1;
			l1.push_front({itemcount[i],i});
			make_set_from_node(t.root_tree,l1);
			l1.pop_front();
		}
	}
	for(ll i=2;i<10;i++)
	{
	    if(arr[i].size()>0)
	    {
	        rule_generate(i);
	    }
	}
	output_file2.close();
}
