

#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <random>
#include <queue>
#include <algorithm>

// #define GENERATION_LIMIT (std::max(20, std::min(75, objectLimit / 2)))
#define GENERATION_LIMIT (std::max(40, std::min(400, objectLimit / 2)))
#define MUTATION_RATE (1.0 / catalogue.size())
#define REPRODUCTION_RATE 0.75
#define POPULATION_LIMIT std::min(1000, objectLimit * 10)

int onePointCrossoverOccurences = 0;
int twoPointCrossoverOccurences = 0;
int uniformCrossoverOccurences = 0;
int formGenerationFromChildrenOccurences = 0;
int formGenerationFromElitismOccurences = 0;
int formGenerationFromMixingOccurences = 0;
int elitistSelectionOccurences = 0;
int rouletteWheelSelectionOccurences = 0;


double GREEDINESS = 0.5;

std::random_device randomDevice;
std::mt19937 gen(randomDevice());

//#define PopulationContainer std::priority_queue<individual, std::deque<individual>, IndividualComparator>
//#define populationContainerInsert population.push

#define PopulationContainer std::vector<individual>
#define populationContainerInsert push_back


int objectLimit;
int weightLimit;

struct object {
    int weight;
    int value;

    friend std::istream &operator>>(std::istream &is, object &object) {
        is >> object.weight;
        is >> object.value;
        return is;
    }
};

std::vector<object> catalogue;

struct individual {
    std::vector<bool> genes;
    int fitness = 0;

    explicit individual(const std::vector<bool> &genes = std::vector<bool>(), int fitness = 0) {
        this->genes = genes;
        this->fitness = fitness;
    }

    bool operator<(const individual &other) const {
        return this->fitness > other.fitness;
    }

    void calculateFitness() {
        int totalValue = 0;
        for (int i = 0; i < genes.size(); i++) {
            if (genes[i]) {
                totalValue += catalogue[i].value;
            }
        }
        fitness = totalValue;
    }

    bool isHealthy() {
        int totalWeight = 0;
        int totalValue = 0;
        for (int i = 0; i < genes.size(); i++) {
            if (genes[i]) {
                totalWeight += catalogue[i].weight;
                totalValue += catalogue[i].value;
            }
        }
        fitness = totalValue;
        return totalWeight < weightLimit;
    }
};

struct IndividualComparator {
    bool operator()(const individual &lhs, const individual &rhs) {
        return lhs.fitness < rhs.fitness;
    }
};

std::vector<object> initializeFromConsole() {
    std::cin >> weightLimit >> objectLimit;
    catalogue.reserve(objectLimit);
    object temp{};
    for (int i = 0; i < objectLimit; i++) {
        std::cin >> temp;
        catalogue.push_back(temp);
    }
    std::sort(catalogue.begin(), catalogue.end(),
              [](const object &lhs, const object &rhs) { return (lhs.value / lhs.weight) > (rhs.value / rhs.weight); });
    return catalogue;
}

std::vector<object> initializeFromFile(const std::string &path) {
    std::ifstream inputFile(path);
    if (!inputFile.is_open()) {
        std::cerr << "Failed to input catalogue. Initialize from console instead. ";
        return initializeFromConsole();
    }
    inputFile >> weightLimit;
    inputFile >> objectLimit;
    catalogue.reserve(objectLimit);
    object temp{};
    for (int i = 0; i < objectLimit; i++) {
        inputFile >> temp;
        catalogue.push_back(temp);
    }
    inputFile.close();
    std::sort(catalogue.begin(), catalogue.end(),
              [](const object &lhs, const object &rhs) { return (lhs.value / lhs.weight) > (rhs.value / rhs.weight); });
    return catalogue;
}


individual generateRandomIndividual() {
    std::vector<bool> genes(objectLimit, false);
    double temporaryGreediness = GREEDINESS;
    double reduction = GREEDINESS / objectLimit;
    double weight = 0;
    for (int i = 0; i < objectLimit; i++) {
        std::bernoulli_distribution distribution(GREEDINESS);
        genes[i] = distribution(gen);
        if (genes[i]) {
            weight += catalogue[i].weight;
            if (weight > weightLimit) {
                genes[i] = false;
                break;
            }
        }
        temporaryGreediness -= reduction;
    }
    individual individual{genes, 0};
    individual.calculateFitness();
    return individual;
}

PopulationContainer generateInitialPopulation(int limit = POPULATION_LIMIT) {
    PopulationContainer population;
    population.reserve(limit);
    while (population.size() < limit) {
        individual temp = generateRandomIndividual();
        population.populationContainerInsert(temp);
    }
    return population;
}

std::vector<individual> elitistSelection(const PopulationContainer &population) {
    std::vector<individual> selection;
    int i = 0;
    while (selection.size() < std::min((int) population.size(), (int) (POPULATION_LIMIT * REPRODUCTION_RATE))) {
        selection.push_back(population[i]);
        i++;
    }
    return selection;
}

std::vector<individual> rouletteWheelSelection(const PopulationContainer &population) {
    std::vector<individual> selection;

    int totalFitness = 0;
    for (const individual &ind: population) {
        totalFitness += ind.fitness;
    }

    std::vector<int> cumulativeProbabilities;
    cumulativeProbabilities.reserve(population.size());
    int cumulativeProbability = 0;
    for (const individual &individual: population) {
        cumulativeProbability += individual.fitness;
        cumulativeProbabilities.push_back(cumulativeProbability);
    }

    std::uniform_int_distribution distribution(0, totalFitness);
    while (selection.size() < std::min((int) population.size(), (int) (POPULATION_LIMIT * REPRODUCTION_RATE))) {
        int randomValue = distribution(gen);

        for (int i = 0; i < population.size(); ++i) {
            if (randomValue <= cumulativeProbabilities[i]) {
                selection.push_back(population[i]);
                break;
            }
        }
    }
    return selection;
}

std::vector<individual> selection(const PopulationContainer &population) {
    std::discrete_distribution<int> distribution({1, 1});
    switch (distribution(gen)) {
        case 0:
            elitistSelectionOccurences++;
            return elitistSelection(population);
        case 1:
            rouletteWheelSelectionOccurences++;
            return rouletteWheelSelection(population);
        default:
            elitistSelectionOccurences++;
            return elitistSelection(population);
    }
}

std::vector<individual> onePointCrossover(const individual &parent1, const individual &parent2) {
    std::vector<individual> children(2);
    std::uniform_int_distribution distribution(1, (int) parent1.genes.size() - 1);
    unsigned int mid = distribution(gen);

    std::vector<bool> genes1(parent1.genes.size());
    std::vector<bool> genes2(parent1.genes.size());

    int i = 0;
    for (; i < mid; i++) {
        genes1[i] = parent1.genes[i];
        genes2[i] = parent2.genes[i];
    }
    int j = 0;
    for (; i < parent1.genes.size(); i++) {
        genes1[i] = parent2.genes[i];
        genes2[i] = parent1.genes[i];
    }

    individual child1(genes1);
    individual child2(genes2);
    children[0] = child1;
    children[1] = child2;
    return children;
}

std::vector<individual> uniformCrossover(const individual &parent1, const individual &parent2) {
    std::vector<individual> children(2);
    std::vector<bool> genes1(parent1.genes.size());
    std::vector<bool> genes2(parent2.genes.size());
    std::bernoulli_distribution distribution(0.5);
    for (int i = 0; i < genes1.size(); i++) {
        if (distribution(gen)) {
            genes1[i] = parent1.genes[i];
            genes2[i] = parent2.genes[i];
        } else {
            genes1[i] = parent2.genes[i];
            genes2[i] = parent1.genes[i];
        }
    }
    individual child1(genes1);
    individual child2(genes2);
    children[0] = child1;
    children[1] = child2;
    return children;
}

std::vector<individual> twoPointCrossover(const individual &parent1, const individual &parent2) {
    std::vector<individual> children(2);
    std::vector<bool> genes1(parent1.genes.size());
    std::vector<bool> genes2(parent2.genes.size());

    std::uniform_int_distribution<size_t> distribution(1, parent1.genes.size() - 1);

    size_t point1 = distribution(gen);
    size_t point2 = distribution(gen);

    while (point1 == point2) {
        point2 = distribution(gen);
    }

    if (point1 > point2) {
        std::swap(point1, point2);
    }

    for (size_t i = 0; i < point1; i++) {
        genes1[i] = parent1.genes[i];
        genes2[i] = parent2.genes[i];
    }

    for (size_t i = point1; i < point2; i++) {
        genes1[i] = parent2.genes[i];
        genes2[i] = parent1.genes[i];
    }

    for (size_t i = point2; i < parent1.genes.size(); i++) {
        genes1[i] = parent1.genes[i];
        genes2[i] = parent2.genes[i];
    }
    individual child1(genes1);
    individual child2(genes2);
    children[0] = child1;
    children[1] = child2;
    return children;
}

std::vector<individual> crossover(const individual &parent1, const individual &parent2) {
    std::discrete_distribution<int> distribution({2, 5, 5});
    switch (distribution(gen)) {
        case 0:
            onePointCrossoverOccurences++;
            return onePointCrossover(parent1, parent2);
        case 1:
            twoPointCrossoverOccurences++;
            return twoPointCrossover(parent1, parent2);
        case 2:
            uniformCrossoverOccurences++;
            return uniformCrossover(parent1, parent2);
        default:
            return onePointCrossover(parent1, parent2);
    }
}

std::vector<individual> reproduction(const std::vector<individual> &parents) {
    std::vector<individual> children;
    for (int i = 0; i < parents.size() - 1; i += 2) {
        for (const auto &child: crossover(parents[i], parents[i + 1])) {
            children.push_back(child);
        }
    }
    return children;
}

std::vector<individual> mutate(std::vector<individual> &children) {
    auto mutationIsNeeded = []() {
        std::bernoulli_distribution distribution(MUTATION_RATE);
        return distribution(gen);
    };
    for (auto &individual: children) {
        for (auto &&gene: individual.genes) {
            if (mutationIsNeeded()) {
                gene = !gene;
            }
        }
    }
    auto newEnd = std::remove_if(children.begin(), children.end(),
                                 [](individual &individual) { return !individual.isHealthy(); });
    children.erase(newEnd, children.end());
    return children;
}


std::vector<individual> &
formNewGenerationFromElitism(std::vector<individual> &population, const std::vector<individual> &children) {
    for (const auto &child: children) {
        population.populationContainerInsert(child);
    }
    std::sort(population.begin(), population.end());
    if (population.size() > POPULATION_LIMIT) {
        population.resize(POPULATION_LIMIT);
    }
    return population;
}


std::vector<individual> &
formNewGenerationFromMixing(std::vector<individual> &population, const std::vector<individual> &children) {
    population.insert(population.end(), children.begin(), children.end());
    std::sort(population.begin(), population.end());
    int halfSize = POPULATION_LIMIT / 2;
    std::vector<individual> remaining(population.begin() + halfSize, population.end());
    std::shuffle(remaining.begin(), remaining.end(), gen);
    population.resize(POPULATION_LIMIT);
    int remainingSize = POPULATION_LIMIT - halfSize;
    remaining.resize(remainingSize);
    std::sort(remaining.begin(), remaining.end());
    std::copy(remaining.begin(), remaining.end(), population.begin() + halfSize);
    return population;
}

std::vector<individual> &
formNewGenerationFromChildren(std::vector<individual> &population, const std::vector<individual> &parents,
                              const std::vector<individual> &children) {
    population = PopulationContainer(children.begin(), children.end());
    int i = 0;
    while (i < parents.size() && population.size() < POPULATION_LIMIT) {
        population.populationContainerInsert(parents[i]);
        i++;
    }
    std::sort(population.begin(), population.end());
    return population;
}


void formNewGeneration(std::vector<individual> &population, const std::vector<individual> &parents,
                       const std::vector<individual> &children) {
    std::discrete_distribution distribution({1.0, 3.0, 2.5});
    switch (distribution(gen)) {
        case 0:
            formGenerationFromChildrenOccurences++;
            formNewGenerationFromChildren(population, parents, children);
            break;
        case 1:
            formNewGenerationFromMixing(population, children);
            formGenerationFromMixingOccurences++;
            break;
        case 2:
            formGenerationFromElitismOccurences++;
            formNewGenerationFromElitism(population, children);
            break;
    }
}


int main(int argc, char *argv[]) {
    if (argc > 1) {
        initializeFromFile(argv[1]);
    } else {
        initializeFromConsole();
    }
    int currentGeneration = 0;
    PopulationContainer population = generateInitialPopulation();
    std::sort(population.begin(), population.end());
    while (currentGeneration < GENERATION_LIMIT) {
        std::vector<individual> parents = selection(population);
        std::vector<individual> children = reproduction(parents);
        mutate(children);
        formNewGeneration(population, parents, children);
        currentGeneration++;
        std::cout << population[0].fitness << std::endl;

    }
    // std::cout << std::endl << "CROSSOVERS:" << std::endl <<
    //           "OnePointCrossover: " << onePointCrossoverOccurences << std::endl <<
    //           "TwoPointCrossover: " << twoPointCrossoverOccurences << std::endl <<
    //           "UniformCrossover : " << uniformCrossoverOccurences << std::endl << std::endl;
    // std::cout << "SELECTIONS" << std::endl <<
    //           "ElitistParentSelection: " << elitistSelectionOccurences << std::endl <<
    //           "RouletteWheelSelection: " << rouletteWheelSelectionOccurences << std::endl << std::endl;
    // std::cout << "GENERATIONS" << std::endl <<
    //           "GenerationsFromChildren: " << formGenerationFromChildrenOccurences << std::endl <<
    //           "GenerationsFromElitism : " << formGenerationFromElitismOccurences << std::endl <<
    //           "GenerationsFromMixing  : " << formGenerationFromMixingOccurences << std::endl;
    return 0;
}



