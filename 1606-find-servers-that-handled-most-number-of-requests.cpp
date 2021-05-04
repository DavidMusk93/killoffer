//
// Created by Steve on 1/24/2021.
//

#include "solver_ex.h"

namespace sun {
    class Server;

    using Compare = std::function<bool(Server *, Server *)>;

    static priority_queue<Server *, deque<Server *>, Compare> min_heap;
    static int maximum_load;

    class Cluster {

    public:
        Cluster(int n) {
            servers_.resize(n);
            for (int i = 0; i < n; ++i) {
                servers_[i].index = i;
                servers_[i].next = &servers_[(i + 1) % n];
            }
        }

        bool handle(int i, int arrival, int load) {
            Server *handler = &servers_[i];
            do {
                if (handler->handle(arrival, load)) {
                    return true;
                } else {
                    handler = handler->next;
                }
            } while (handler->index != i);
            return false;
        }

        vector<int> findMostBusyServer() {
            vector<int> ans;
            for (auto &server:servers_) {
                if (server.load_count == maximum_load) {
                    ans.push_back(server.index);
                }
            }
            return ans;
        }

        struct Server {
            int index{};
            int load_count{};
            int available_timestamp{};
            Server *next{};

            bool handle(int arrival, int load) {
                if (arrival < available_timestamp) {
                    return false;
                }
                available_timestamp = arrival + load;
                if (maximum_load < ++load_count) {
                    maximum_load = load_count;
                }
                return true;
            }
        };

    private:
        std::vector<Server> servers_;
    };
}

class Solution {
public:
    vector<int> busiestServers(int k, vector<int> &arrival, vector<int> &load) {
        using Server=sun::Cluster::Server;
        sun::Compare fn=[](Server*l,Server*r){};
        sun::maximum_load = 0;
        sun::Cluster cluster(k);
        const int N = arrival.size();
        for (int i = 0; i < N; ++i) {
            cluster.handle(i % k, arrival[i], load[i]);
        }
        return cluster.findMostBusyServer();
    }
};

MAIN() {
    int __i = 0;
#define __TEST(x) cout<<'['<<++__i<<"-th] ";TEST(expect,x,arrival,load)
    PREREQUISITES(busiestServers);
    vector<int> arrival{1, 2, 3, 4, 5};
    vector<int> load{5, 2, 3, 3, 3};
    vector<int> expect{1};
    __TEST(3);
    arrival = {1, 2, 3, 4};
    load = {1, 2, 1, 2};
    expect = {0};
    __TEST(3);
    arrival = {1, 2, 3};
    load = {10, 12, 11};
    expect = {0, 1, 2};
    __TEST(3);
    arrival = {1, 2, 3, 4, 8, 9, 10};
    load = {5, 2, 10, 3, 1, 2, 2};
    expect = {1};
    __TEST(3);
    arrival = {1};
    load = {1};
    expect = {0};
    __TEST(1);
}