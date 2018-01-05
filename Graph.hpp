#ifndef GRAPH_HPP
#define GRAPH_HPP
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <exception>

template <typename Node, typename Hash = std::hash<Node>, typename Pred = std::equal_to<Node>>
class Graph
{
protected:
    std::unordered_map<Node, std::unordered_set<Node, Hash, Pred>, Hash, Pred> adjacent;
public:
    int vertex;
    int edge;
    
    Graph(int v) : vertex(v), edge(0) {}
    Graph() : Graph(0) {}
    virtual void addVertex(Node v) 
    {
        adjacent[v] = std::unordered_set<Node, Hash, Pred>();
        vertex++;
    }
    virtual void delVertex(Node v) {}
    virtual void addEdge(Node v, Node w) {}
    virtual void delEdge(Node v, Node w) {}
    
    using dfs_result_type = std::unordered_map<Node, bool, Hash, Pred>;
    dfs_result_type marked;
    dfs_result_type& dfs(Node v)
    {
        if (marked.size() != vertex)
        {
            marked.clear();
            for (auto &i = adjacent.begin(); i != adjacent.end(); i++)
            {
                marked[i->first] = false;
            }
        }

        marked[v] = true;
        for (auto &w : adjacent[v])
            if (!marked[w])
                dfs(w);

        return marked;
    }

    class UF
    {
    private:
        std::unordered_map<Node, int> size;
        std::unordered_map<Node, Node> id;
        void merge(Node v, Node w)
        {
            Node &i = find(v);
            Node &j = find(w);
            if (i == j)
                return;
            if (size[i] < size[j])
            {
                id[i] = j;
                size[j] += size[i];
            }
            else
            {
                id[j] = i;
                size[i] += size[j];
            }
        }
        
        Node& find(Node v)
        {
            while (v != id[v])
                v = find(v);
            return v;
        }
        
    public: 
        UF() : size(), id()
        {
            for (auto &i = adjacent.begin(); i != adjacent.end(); i++)
            {
                size[i->first] = 1;
                id[i->first] = i->first;
            }
            for (auto i = this->adjacent.begin(); i != this->adjacent.end(); i++)
                for (auto &w : i->second)
                    merge(i->first, w);
        }

        bool connected(Node v, Node w)
        {
            return find(v) == find(w);
        }
    };
};

template <typename Node, typename Hash = std::hash<Node>, typename Pred = std::equal_to<Node>>
class DirectedGraph : public Graph<Node>
{
private:
    std::unordered_map<Node, std::unordered_set<Node, Hash, Pred>, Hash, Pred> reverse;

public:
    bool stable = false;
    DirectedGraph(int v, bool s) : Graph(v), stable(s) {}
    DirectedGraph(bool s) : DirectedGraph(0, s) {}
    DirectedGraph() : DirectedGraph(0, false) {}
    DirectedGraph& reverseGraph()
    {
        if (stable)
        {
            DirectedGraph r(true);
            r.adjacent = reverse;
            r.reverse = this->adjacent;
            return r;
        }
        else
        {
            reverse.clear();
            for (auto i = this->adjacent.begin(); i != this->adjacent.end(); i++)
                for (auto &w : i->second)
                    reverse.addEdge(w, i->first);
            DirectedGraph r(true);
            r.adjacent = reverse;
            r.reverse = this->adjacent;
            return r;
        }
    }

    void addVertex(Node v) override
    {
        this->adjacent[v] = std::unordered_set<Node, Hash, Pred>();
        if (stable)
            this->reverse[v] = std::unordered_set<Node, Hash, Pred>();
        this->vertex++;
    }

    void addEdge(Node v, Node w) override
    {
        if (!stable)
        {
            auto n = this->adjacent.find(v);
            if (n == this->adjacent.end())
                throw std::runtime_error("no such node");
            else
            {
                n->second.insert(w);
            }
        }
        else
        {
            auto vv = this->adjacent.find(v);
            auto ww = this->reverse.find(w);
            if (vv == this->adjacent.end() || ww == this->reverse.end())
                throw std::runtime_error("no such node");
            else
            {
                vv->second.insert(w);
                ww->second.insert(v);
            }
        }
        this->edge++;
    }
    
    void delEdge(Node v, Node w) override
    {
        auto n = this->adjacent.find(v);
        if (n == this->adjacent.end())
            throw std::runtime_error("no such node");
        else
        {
            n->second.erase(w);
        }
        this->edge--;
    }

    void delVertex(Node v) override
    {
        if (!stable)
        {
            this->adjacent.erase(v);
        }
        else
        {
            for (auto &w : this->reverse[v])
                delEdge(w, v);
            this->adjacent.erase(v);
            this->reverse.erase(v);
        }
        this->vertex--;
    }
};

template <typename Node, typename Hash = std::hash<Node>, typename Pred = std::equal_to<Node>>
class IndirectedGraph : public Graph<Node>
{
public:   
    IndirectedGraph(int v) : Graph(v) {}
    IndirectedGraph() : IndirectedGraph(0) {}
    void addEdge(Node v, Node w) override
    {
        auto vv = this->adjacent.find(v);
        auto ww = this->adjacent.find(w);
        if (vv == this->adjacent.find(v) || ww == this->adjacent.find(w))
            throw std::runtime_error("no such node");
        else
        {
            vv->second.insert(w);
            ww->second.insert(v);
            this->edge++;
        }
    }

    void delEdge(Node v, Node w) override
    {
        auto vv = this->adjacent.find(v);
        auto ww = this->adjacent.find(w);
        if (vv == this->adjacent.find(v) || ww == this->adjacent.find(w))
            throw std::runtime_error("no such node");
        else
        {
            vv->second.erase(w);
            ww->second.erase(v);
            this->edge--;
        }
    }

    void delVertex(Node v) override
    {
        for (auto &w : this->adjacent[v])
            delEdge(v, w);
        this->adjacent.erase(v);
        this->vertex--;
    }
};
#endif