#include "MagicalContainer.hpp"
namespace ariel
{

    // Default constructor
    MagicalContainer::MagicalContainer() {}
    // Copy constructor
    MagicalContainer::MagicalContainer(const MagicalContainer &other) : elements(other.elements) {}
    // move constructor
    MagicalContainer::MagicalContainer(MagicalContainer &&other) noexcept : elements(std::move(other.elements)) {}
    // Copy assignment operator
    MagicalContainer &MagicalContainer ::operator=(const MagicalContainer &other)
    {
        if (this != &other)
        {
            elements = other.elements;
        }
        return *this;
    }

    // Move assignment operator
    MagicalContainer &MagicalContainer ::operator=(MagicalContainer &&other) noexcept
    {
        if (this != &other)
        {
            elements = std::move(other.elements);
        }
        return *this;
    }

    // Destructor
    MagicalContainer::~MagicalContainer() {}

    // Add element
    void MagicalContainer::addElement(int element) {
        auto it = lower_bound(elements.begin(), elements.end(), element);
        elements.insert(it, element);
        updatePrimes();
    }

    //remove element
    void MagicalContainer::removeElement(int element) {
        auto it = lower_bound(elements.begin(), elements.end(), element);
        if (it != elements.end() && *it == element) {
            elements.erase(it);
        } else {
            throw std::runtime_error("Element not found in the container");
        }
        updatePrimes();
    }

    // set container
    void MagicalContainer::setelem(vector<int> &elem)
    {
        elements = elem;
    }
    // get container
    vector<int> &MagicalContainer::getelem()
    {
        return elements;
    }

    // Size of the container
    int MagicalContainer::size() const
    {
        return elements.size();
    }
    // Get element at index
    int MagicalContainer::getElementAt(int index) const
    {
        if (index < 0 || index >= static_cast<int>(elements.size()))
        {
            throw std::out_of_range("Index is out of range");
        }
        return elements.at(static_cast<std::vector<int>::size_type>(index));
    }
    bool MagicalContainer::is_prime(int num) const
    {
        if (num <= 1)
            return false;
        for (int i = 2; i * i <= num; ++i)
        {
            if (num % i == 0)
                return false;
        }
        return true;
    }
    void MagicalContainer::updatePrimes() {
        primes.clear();
        for (size_t i = 0; i < elements.size(); ++i) {
            if (is_prime(elements[i])) {
                primes.push_back(&elements[i]);
            }
        }
    }


    // AscendingIterator----------------------------------------------------------------------------------------------------------------------------------------------

    MagicalContainer::AscendingIterator::AscendingIterator(const MagicalContainer &container)
        : container(container), index(0) {}

    MagicalContainer::AscendingIterator::AscendingIterator(const MagicalContainer &container, int index)
        : container(container), index(index) {}

    // Copy constructor
    MagicalContainer::AscendingIterator::AscendingIterator(const AscendingIterator &other)
        : container(other.container), index(other.index) {}

    // Destructor
    MagicalContainer::AscendingIterator::~AscendingIterator() {}

    // Assignment operator
    MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator=(const AscendingIterator &other)
    {
        if (&container != &other.container)
        {
            throw std::runtime_error("Iterators are pointing to different containers");
        }
        if (this != &other)
        {
            this->index = other.index;
        }
        return *this;
    }

    // increment operator
    MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator++()
    {
        if (index >= container.size())
        {
            throw std::runtime_error("Iterator increment beyond end");
        }
        index++;
        return *this;
    }

    // Dereference operator
    int MagicalContainer::AscendingIterator::operator*() const
    {
        if (index < 0 || index >= container.size())
        {
            throw std::out_of_range("Iterator out of bounds");
        }
        return container.getElementAt(index);
    }

    // Equality comparison
    bool MagicalContainer::AscendingIterator::operator==(const AscendingIterator &other) const
    {
        return this->index == other.index && &this->container == &other.container;
    }

    // Inequality comparison
    bool MagicalContainer::AscendingIterator::operator!=(const AscendingIterator &other) const
    {
        return !(*this == other);
    }

    // GT, LT comparison operators
    bool MagicalContainer::AscendingIterator::operator>(const AscendingIterator &other) const
    {
        if (&this->container != &other.container)
        {
            throw std::invalid_argument("Comparing iterators from different containers is not allowed");
        }
        return this->index > other.index;
    }

    bool MagicalContainer::AscendingIterator::operator<(const AscendingIterator &other) const
    {
        if (&this->container != &other.container)
        {
            throw std::invalid_argument("Comparing iterators from different containers is not allowed");
        }
        return this->index < other.index;
    }

    MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::begin()
    {
        return MagicalContainer::AscendingIterator(container, 0);
    }

    MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::end()
    {
        return AscendingIterator(container, container.size());
    }

    // SideCrossIterator-------------------------------------------------------------------------------------------------------------------------------------------------

    MagicalContainer::SideCrossIterator::SideCrossIterator(const MagicalContainer &container) : container(container), index(0) {}

    MagicalContainer::SideCrossIterator::SideCrossIterator(const MagicalContainer &container, int index) : container(container), index(index) {}

    MagicalContainer::SideCrossIterator::SideCrossIterator(const SideCrossIterator &other) : container(other.container), index(other.index) {}

    MagicalContainer::SideCrossIterator::~SideCrossIterator() {}

    MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator=(const SideCrossIterator &other)
    {
        if (&container != &other.container)
        {
            throw std::runtime_error("Iterators are pointing to different containers");
        }
        if (this != &other)
        {
            this->index = other.index;
        }
        return *this;
    }

    // increment operator
    MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::operator++()
    {
        if (index >= container.size())
        {
            throw std::runtime_error("Iterator increment beyond end");
        }
        index++;
        return *this;
    }

    // Dereference operator
    int MagicalContainer::SideCrossIterator::operator*() const
    {
        if (!(index % 2))
        {
            return container.elements.at((std::vector<int>::size_type)(index / 2));
        }
        else
        {
            return container.elements.at((std::vector<int>::size_type)(container.size() - 1 - (index - 1) / 2));
        }
    }

    bool MagicalContainer::SideCrossIterator::operator==(const SideCrossIterator &other) const
    {
        return this->index == other.index && &(this->container) == &(other.container);
    }

    bool MagicalContainer::SideCrossIterator::operator!=(const SideCrossIterator &other) const
    {
        return !(*this == other);
    }

    bool MagicalContainer::SideCrossIterator::operator>(const SideCrossIterator &other) const
    {
        if (&(this->container) != &(other.container))
        {
            throw std::invalid_argument("Comparing iterators from different containers is not allowed");
        }
        return this->index > other.index;
    }

    bool MagicalContainer::SideCrossIterator::operator<(const SideCrossIterator &other) const
    {
        if (&(this->container) != &(other.container))
        {
            throw std::invalid_argument("Comparing iterators from different containers is not allowed");
        }
        return this->index < other.index;
    }

    MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::begin()
    {
        return SideCrossIterator(container, 0);
    }

    MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::end()
    {
        return SideCrossIterator(container, container.size());
    }

    // PrimeIterator--------------------------------------------------------------------------------------------------------------------------------------------------

    MagicalContainer::PrimeIterator::PrimeIterator(const MagicalContainer &container)
        : container(container), index(0) {}

    MagicalContainer::PrimeIterator::PrimeIterator(const MagicalContainer &container, int index)
        : container(container), index(index) {}

    // Copy constructor
    MagicalContainer::PrimeIterator::PrimeIterator(const PrimeIterator &other)
        : container(other.container), index(other.index) {}

    // Destructor
    MagicalContainer::PrimeIterator::~PrimeIterator() {}

    // Assignment operator
    MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator=(const PrimeIterator &other)
    {
        if (&container != &other.container)
        {
            throw std::runtime_error("Iterators are pointing to different containers");
        }
        if (this != &other)
        {
            this->index = other.index;
        }
        return *this;
    }

    // increment operator
    MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::operator++()
    {
        if (index >= container.primes.size())
        {
            throw std::runtime_error("Iterator increment beyond end");
        }
        index++;
        return *this;
    }

    // Dereference operator
    int MagicalContainer::PrimeIterator::operator*() const
    {
        if (index >= container.primes.size())
        {
            throw std::out_of_range("Iterator out of range");
        }
        return *container.primes.at((std::vector<int *>::size_type)(index));
    }

    // Equality comparison
    bool MagicalContainer::PrimeIterator::operator==(const PrimeIterator &other) const
    {
        return this->index == other.index && &this->container == &other.container;
    }

    // Inequality comparison
    bool MagicalContainer::PrimeIterator::operator!=(const PrimeIterator &other) const
    {
        return !(*this == other);
    }

    // GT, LT comparison operators
    bool MagicalContainer::PrimeIterator::operator>(const PrimeIterator &other) const
    {
        if (&this->container != &other.container)
        {
            throw std::invalid_argument("Comparing iterators from different containers is not allowed");
        }
        return this->index > other.index;
    }

    bool MagicalContainer::PrimeIterator::operator<(const PrimeIterator &other) const
    {
        if (&this->container != &other.container)
        {
            throw std::invalid_argument("Comparing iterators from different containers is not allowed");
        }
        return this->index < other.index;
    }

    MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::begin()
    {
        return MagicalContainer::PrimeIterator(container, 0);
    }

    MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::end()
    {
        return PrimeIterator(container, container.primes.size());
    }

}
