#include <iostream>
#include <vector>
using namespace std;

const int N = 2; // Number of states
const int T = 3; // Number of observations

double pi[N] = {0.5, 0.5};
double a[N][N] = {{0.7, 0.3}, {0.4, 0.6}};
double b[N][T] = {{0.1, 0.4, 0.5}, {0.6, 0.3, 0.1}};
int observations[T] = {0, 1, 0};

vector<vector<double>> alpha(T, vector<double>(N));
vector<vector<double>> beta(T, vector<double>(N));
vector<int> q(T);

void forward(){
    // Initialize alpha
    for (int i = 0; i < N; i++) {
        alpha[0][i] = pi[i] * b[i][observations[0]];
    }
    // Compute alpha
    for (int t = 1; t < T; t++) {
        for (int i = 0; i < N; i++) {
            double sum = 0;
            for (int j = 0; j < N; j++) {
                sum += alpha[t-1][j] * a[j][i];
            }
            alpha[t][i] = sum * b[i][observations[t]];
        }
    }
}

void backward(){
    // Initialize beta
    for (int i = 0; i < N; i++) {
        beta[T-1][i] = 1;
    }
    // Compute beta
    for (int t = T-2; t >= 0; t--) {
        for (int i = 0; i < N; i++) {
            double sum = 0;
            for (int j = 0; j < N; j++) {
                sum += beta[t+1][j] * a[i][j] * b[j][observations[t+1]];
            }
            beta[t][i] = sum;
        }
    }
}

void viterbi(){
    // Compute the most likely sequence of hidden states
    for (int t = 0; t < T; t++) {
        double maxProb = 0;
        int maxState = 0;
        for (int i = 0; i < N; i++) {
            double prob = alpha[t][i] * beta[t][i];
            if (prob > maxProb) {
                maxProb = prob;
                maxState = i;
            }
        }
        q[t] = maxState;
    }
}

int main() {
    forward();
    backward();
    viterbi();
    // Print the most likely sequence of hidden states
    cout << "Most likely sequence of hidden states:" << endl;
    for (int i = 0 = 0; i < T; i++) {
cout << q[i] << " ";
}
return 0;
}
