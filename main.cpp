#include <iostream>
#include <array>
#include <algorithm>
#include <cstring>

using Int = std::uint8_t;
using Node = std::array<Int, 3>;
using Edge = std::array<Int, 2>;
constexpr int N = 12;

//constexpr std::array<std::array<Int, 3>, 4> g_nodes = {{
//                                                               {{Int(0), Int(4), Int(8)}},
//                                                               {{Int(1), Int(7), Int(11)}},
//                                                               {{Int(2), Int(5), Int(10)}},
//                                                               {{Int(3), Int(6), Int(9)}}
//                                                       }};

constexpr std::array<std::array<Int, 3>, 4> g_nodes = {{
                                                               {{Int(0), Int(1), Int(2)}},
                                                               {{Int(3), Int(4), Int(10)}},
                                                               {{Int(5), Int(6), Int(7)}},
                                                               {{Int(8), Int(9), Int(11)}}
                                                       }};
constexpr std::array<std::array<Int, 2>, N/2> g_edges = {{
                                                               {{Int(0),Int(1)}},
                                                               {{Int(2),Int(3)}},
                                                               {{Int(4),Int(5)}},
                                                               {{Int(6),Int(7)}},
                                                               {{Int(8),Int(9)}},
                                                               {{Int(10),Int(11)}}
                                                       }};
template<int n>
constexpr auto invert_permutation(std::array<Int, n>& perm){
    std::array<Int, n> inverse;
    for (int i = 0; i < n; ++i) {
        inverse[i] = std::distance(perm.begin(), std::find(perm.begin(), perm.end(), i));
    }
    return inverse;
}

std::array<Int, N> g_edges_inv;
std::array<Int, N> g_nodes_inv;

template<int h>
bool is_valid(
        std::array<Int, h> const& half_edges)
{
    std::array<Node, h/3> nodes;
    std::array<Edge, h/2> edges;
    auto nodes_data = (Int*)nodes.data();
    auto g_nodes_data = (Int*)g_nodes.data();
    auto edges_data = (Int*)edges.data();
    auto g_edges_data = (Int*)g_edges.data();
    for(int i = 0; i < h; ++i){
        nodes_data[g_nodes_inv[i]] = half_edges[i];
        edges_data[g_edges_inv[i]] = half_edges[i];
    }
    for(auto& n : nodes)
        std::sort(n.begin(), n.end());
    std::sort(nodes.begin(), nodes.end());
    if(std::memcmp(nodes.data(), g_nodes.data(), h * sizeof(Int)))
        return false;
    for(auto& e : edges)
        std::sort(e.begin(), e.end());
    std::sort(edges.begin(), edges.end());
    return !std::memcmp(edges.data(), g_edges.data(), h * sizeof(Int));
}
int main() {

    auto reinterpreted_nodes = *(std::array<Int,N>*)&g_nodes;
    auto reinterpreted_edges = *(std::array<Int,N>*)&g_edges;
    g_nodes_inv = invert_permutation<N>(reinterpreted_nodes);
    g_edges_inv = invert_permutation<N>(reinterpreted_edges);

    std::array<Int, N> g_half_edges = {0,1,2,3,4,5,6,7,8,9,10,11};
    int count = 0;
    int i = 0;
    do {
        if(is_valid<N>(g_half_edges)) {
            ++count;
            for(auto a : g_half_edges)
                std::cout << int(a) << ' ';
            std::cout << std::endl;
        }
        ++i;
        //if(i % 100000 == 0) std::cout << i << std::endl;
    }while(std::next_permutation(g_half_edges.begin(), g_half_edges.end()));
    std::cout << count << std::endl;




}


