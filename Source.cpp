#include <iostream>
#include <queue>
#include <string>

using namespace std;

const int SIZE = 100;

class SocialNetwork {
private:
    struct Human {
        string name;
        int id;
        Human(string n = "", int i = -1) : name(n), id(i) {}
    };

    bool busyids[SIZE];
    Human people[SIZE];
    int friend_matrix[SIZE][SIZE];
    int peopleCount;

    Human findManByName(const string& name) {
        for (int i = 0; i < peopleCount; i++) {
            if (people[i].name == name) {
                return people[i];
            }
        }
        return Human();
    }

public:
    SocialNetwork() : peopleCount(0) {
        for (int i = 0; i < SIZE; ++i) {
            busyids[i] = false;
            for (int j = 0; j < SIZE; ++j) {
                friend_matrix[i][j] = 0;
            }
        }
    }

    void addnewMan(const string& name) {
        Human man = findManByName(name);
        if (man.id >= 0)
            return;
        int i = 0;
        for (; i < SIZE; i++)
            if (!busyids[i])
                break;
        busyids[i] = true;
        people[peopleCount++] = Human(name, i);
    }

    void delMan(const string& name) {
        Human man = findManByName(name);
        if (man.id < 0)
            return;
        busyids[man.id] = false;
        for (int i = 0; i < peopleCount; i++) {
            friend_matrix[i][man.id] = 0;
            friend_matrix[man.id][i] = 0;
        }
        for (int i = man.id; i < peopleCount - 1; ++i) {
            people[i] = people[i + 1];
            people[i].id = i;
        }
        peopleCount--;
    }

    void addFriendship(const string& name_1, const string& name_2) {
        Human m1 = findManByName(name_1);
        Human m2 = findManByName(name_2);
        if (m1.id < 0 || m2.id < 0)
            return;
        friend_matrix[m1.id][m2.id] = 1;
        friend_matrix[m2.id][m1.id] = 1;
    }

    void findAllPairsWithinThreeHandshakes() {
        for (int i = 0; i < peopleCount; ++i) {
            int distance[SIZE] = { 0 };
            for (int j = 0; j < SIZE; ++j) {
                distance[j] = -1;
            }
            queue<int> q;

            distance[i] = 0;
            q.push(i);

            while (!q.empty()) {
                int currentNode = q.front();
                q.pop();

                for (int neighbor = 0; neighbor < SIZE; ++neighbor) {
                    if (friend_matrix[currentNode][neighbor] == 1 && distance[neighbor] == -1) {
                        distance[neighbor] = distance[currentNode] + 1;
                        q.push(neighbor);
                    }
                }
            }

            for (int j = 0; j < peopleCount; ++j) {
                if (distance[j] > 0 && distance[j] <= 3) {
                    cout << "Pair: (" << people[i].name << ", " << people[j].name << ") with distance " << distance[j] << endl;
                }
            }
        }
    }
};

int main() {
    SocialNetwork network;

    network.addnewMan("Alice");
    network.addnewMan("Boris");
    network.addnewMan("Matvey");
    network.addnewMan("David");
    network.addnewMan("Eva");
    network.addnewMan("Fedy");
    network.addnewMan("Ivan");
    network.addnewMan("Misha"); 

    network.addFriendship("Alice", "Boris");
    network.addFriendship("Alice", "Eva");
    network.addFriendship("Boris", "Matvey");
    network.addFriendship("Matvey", "David");
    network.addFriendship("David", "Eva");
    network.addFriendship("Fedy", "Alice");
    network.addFriendship("Fedy", "David");
    network.addFriendship("Ivan", "Boris");
    network.addFriendship("Ivan", "Misha");

    network.findAllPairsWithinThreeHandshakes();

    return 0;
}