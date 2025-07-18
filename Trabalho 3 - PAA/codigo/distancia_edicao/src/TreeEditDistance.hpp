#include "memory"
#include <unordered_map>
#include <utility>
#include <functional>

using namespace std;

template <typename T>
int custoDeletar(shared_ptr<No<T>>& no) {
    return 1; // ou outro custo
}

template <typename T>
int custoInserir(shared_ptr<No<T>>& no) {
    return 1; // ou outro custo
}

template <typename T>
int custoSubstituir(shared_ptr<No<T>>& no1, shared_ptr<No<T>>& no2) {
    return no1->getLabel() == no2->getLabel() ? 0 : 1;
}

template <typename T>
int TEDHelper(shared_ptr<No<T>> no1, shared_ptr<No<T>> no2, unordered_map<pair<shared_ptr<No<T>>, shared_ptr<No<T>>>, int, hash<pair<shared_ptr<No<T>>, shared_ptr<No<T>>>>> &memo) {
    if (!no1 && !no2) return 0; // Both nodes are null
    if (!no1) return custoInserir(no2) + TEDHelper(nullptr, no2->getFilhos().empty() ? nullptr : no2->getFilhos()[0], memo); // Insert all nodes of no2
    if (!no2) return custoDeletar(no1) + TEDHelper(no1->getFilhos().empty() ? nullptr : no1->getFilhos()[0], nullptr, memo); // Delete all nodes of no1

    auto key = make_pair(no1, no2);
    if (memo.find(key) != memo.end()) return memo[key];

    int costSubstitute = custoSubstituir(no1, no2);

    int cost = costSubstitute + TEDHelper(no1->getFilhos().empty() ? nullptr : no1->getFilhos()[0],
                                          no2->getFilhos().empty() ? nullptr : no2->getFilhos()[0], memo);

    memo[key] = cost;
    return cost;
}

// Simplified Tree Edit Distance function
template <typename T>
int TED(Tree<T>& T1, Tree<T>& T2) {
    auto nodes1 = T1.getNodesPostOrder();
    auto nodes2 = T2.getNodesPostOrder();

    int n = nodes1.size();
    int m = nodes2.size();

    // Initialize the DP table
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    // Base cases: Deleting all nodes from T1 or inserting all nodes into T2
    for (int i = 1; i <= n; ++i) {
        dp[i][0] = dp[i - 1][0] + custoDeletar(nodes1[i - 1]);
    }
    for (int j = 1; j <= m; ++j) {
        dp[0][j] = dp[0][j - 1] + custoInserir(nodes2[j - 1]);
    }

    // Fill the DP table
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            int costDelete = dp[i - 1][j] + custoDeletar(nodes1[i - 1]);
            int costInsert = dp[i][j - 1] + custoInserir(nodes2[j - 1]);
            int costSubstitute = dp[i - 1][j - 1] + custoSubstituir(nodes1[i - 1], nodes2[j - 1]);

            dp[i][j] = min({costDelete, costInsert, costSubstitute});
        }
    }

    // Return the edit distance between the two trees
    return dp[n][m];
}

// Custom hash function for std::pair of shared_ptr
namespace std {
    template <typename T>
    struct hash<pair<shared_ptr<No<T>>, shared_ptr<No<T>>>> {
        size_t operator()(const pair<shared_ptr<No<T>>, shared_ptr<No<T>>>& p) const {
            auto h1 = hash<shared_ptr<No<T>>>()(p.first);
            auto h2 = hash<shared_ptr<No<T>>>()(p.second);
            return h1 ^ (h2 << 1); // Combine the two hash values
        }
    };
}