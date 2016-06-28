#ifndef MODULE_TREES_BST_HXX
#define MODULE_TREES_BST_HXX

#include <memory>

namespace SHA_Trees
{
  template <typename Iterator, typename Compare, typename IsEqual>
  class BST
  {
    typedef typename Iterator::value_type Value_Type;
    public:
      /// Build - Construct in a na�ve way a Binary Search Tree given an unordered sequence of elements.
      ///
      /// @param beginFirst,endFisrt,beginSecond,endSecond - iterators to the initial and final positions of
      /// the sequence used to build the tree. The range used is [first,last), which contains
      /// all the elements between first and last, including the element pointed by first but
      /// not the element pointed by last.
      ///
      /// @complexity O(n * m).
      ///
      /// @return Binary Search Tree pointer to be owned, nullptr if construction failed.
      static std::unique_ptr<BST> Build(const Iterator& begin, const Iterator& end)
      {
        if (begin >= end)
          return  nullptr;

        std::unique_ptr<BST> root = std::unique_ptr<BST>(new BST(*begin));

        // Insert all remaining elements within the tree
        for (Iterator it = begin + 1; it != end; ++it)
          root->Insert(*it);

        return root;
      }

      /// BuildFromSorted - Construct a Balanced Binary Search Tree given an ordered sequence of elements.
      ///
      /// @param beginFirst,endFisrt,beginSecond,endSecond - iterators to the initial and final positions of
      /// the sequence used to build the tree. The range used is [first,last), which contains
      /// all the elements between first and last, including the element pointed by first but
      /// not the element pointed by last.
      ///
      /// @complexity O(n).
      ///
      /// @Warning the algorithm does not check the validity on data order; using this algorithm with
      /// unordored data will most likely result in an invalid BST. (Can be checked using IsValid method).
      ///
      /// @return Binary Search Tree pointer to be owned, nullptr if construction failed.
      static std::unique_ptr<BST> BuildFromSorted(const Iterator& begin, const Iterator& end)
      {
        if (begin >= end)
          return nullptr;

        const Iterator middle = begin + (std::distance(begin,end) / 2);
        std::unique_ptr<BST> root = std::unique_ptr<BST>(new BST(*middle));

        // Recursively insert both children
        root->SetLeftChild(std::move(BuildFromSorted(begin, middle)));
        root->SetRightChild(std::move(BuildFromSorted(middle + 1, end)));

        return root;
      }

      /// Find the first a binary search tree for a specific key.
      ///
      /// @complexity O(h), where h may be n in worst case balancement. Equal to log(n) with a balanced tree.
      ///
      /// @param data, data value to be found within the current BST.
      ///
      /// @return first BST node matching the data.
      const BST* Find(const Value_Type& data)
      {
        // Key found returns node
        if (IsEqual()(this->data, data))
          return this;

        // Key is less than current node - search in left subtree
        if (Compare()(data, this->data))
          return this->leftChild ? this->leftChild->Find(data) : nullptr;

        // Search in right subtree
        return this->rightChild ? this->rightChild->Find(data) : nullptr;
      }

      /// Append a new Binary Search Tree node at the right position with current value.
      ///
      /// @complexity O(n).
      ///
      /// @param data, data value to be added to the current BST.
      void Insert(const Value_Type& data)
      {
        // Key is lower or equal than current root - Insert on the left side
        if (Compare()(data, this->data))
        {
          if (!this->leftChild)
            this->SetLeftChild(std::move(std::unique_ptr<BST>(new BST(data))));
          else
            this->leftChild->Insert(data);
        }
        // Key is greater than current root - Insert on the right side
        else
        {
          if (!this->rightChild)
            this->SetRightChild(std::move(std::unique_ptr<BST>(new BST(data))));
          else
            this->rightChild->Insert(data);
        }
      }

      /// Check if the Binary Search Tree is balanced.
      /// Compare the smallest branch to the biggest one to determine the balancement.
      ///
      /// @return wheter or not the tree is balanced (true) or not (false).
      bool IsBlanced() const { return this->MaxHeight() - this->MinHeight() <= 1; }

      /// Check validity of the Binary Search Tree.
      /// Recursively check if subtrees do not violate any of the rules defined by a BST.
      ///
      /// @return wheter or not the tree is a valid Binary Search Tree (true) or not (false).
      bool IsValid() const
      {
        // Left child exists and has bigger value than its parent - Does not respect BST rules
        if (this->GetLeftChild() && !Compare()(this->GetLeftChild()->GetData(), this->GetData()))
          return false;

        // Right child exists and has smaller or equal value of its parent - Does not respect BST rules
        if (this->GetRightChild() && Compare()(this->GetRightChild()->GetData(), this->GetData()))
          return false;

        // Recursively check subtrees
        return ((!this->GetLeftChild() || this->GetLeftChild()->IsValid()) &&
                (!this->GetRightChild() || this->GetRightChild()->IsValid()));
      }

      /// Returns the number of nodes composing the BST.
      ///
      /// Complexity O(n)
      ///
      /// @return number of nodes composing the tree.
      std::size_t Size() const
      {
        return 1 + ((this->GetLeftChild()) ? this->GetLeftChild()->Size() : 0)
                 + ((this->GetRightChild()) ? this->GetRightChild()->Size() : 0);
      }

      /// Returns the smallest branch height.
      ///
      /// Complexity O(n)
      ///
      /// @return smallest branch height composing the tree.
      std::size_t MinHeight() const
      {
        return 1 + std::min(((this->GetLeftChild()) ? this->GetLeftChild()->MinHeight() : 0),
                            ((this->GetRightChild()) ? this->GetRightChild()->MinHeight() : 0));
      }

      /// Returns the biggest branch height.
      ///
      /// Complexity O(n)
      ///
      /// @return biggest branch height composing the tree.
      std::size_t MaxHeight() const
      {
        return 1 + std::max(((this->GetLeftChild()) ? this->GetLeftChild()->MaxHeight() : 0),
                            ((this->GetRightChild()) ? this->GetRightChild()->MaxHeight() : 0));
      }

      Value_Type GetData() const { return this->data; }
      const BST* GetLeftChild() const { return this->leftChild.get(); }
      const BST* GetRightChild() const { return this->rightChild.get(); }

    private:
      BST(const Value_Type& data) : data(data) {}
      BST(BST&) {}           // Not Implemented
      BST operator=(BST&) {} // Not Implemented

      void SetLeftChild(std::unique_ptr<BST> bst) { this->leftChild = std::move(bst); }
      void SetRightChild(std::unique_ptr<BST> bst) { this->rightChild = std::move(bst); }

      typename Iterator::value_type data;
      std::unique_ptr<BST> leftChild;
      std::unique_ptr<BST> rightChild;
  };
};

#endif() // MODULE_TREES_BST_HXX