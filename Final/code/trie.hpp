//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org
//This file is licensed to you under the MIT license

#ifndef TRIE_HPP
#define TRIE_HPP

#include <cstddef>
#include <array>
#include <vector>
#include <string>
#include <memory>

namespace trie
{
	//trie interface
	/*
	void insert(const std::string&, std::size_t)
	std::size_t find(const std::string&) const
	bool remove(const std::string&)
	std::size_t size() const
	bool empty() const
	std::vector<std::string> keys_with_prefix(const std::string&) const
	std::vector<std::string> keys() const
	std::vector<std::string> keys_with_pattern(const std::string&) const
	void clear()
	*/
	class r_way_trie final
	{
		struct trie_node final
		{
			std::size_t val = npos;
			std::unique_ptr<std::array<std::unique_ptr<trie_node>, 26>> children;
		};

		static std::unique_ptr<trie_node>& child(std::unique_ptr<trie_node>& node, std::size_t i)
		{
			//assert node != nullptr && node->children != nullptr
			return node->children->operator[](i);
		}

		static const trie_node* child(const trie_node* node, std::size_t i)
		{
			//assert node != nullptr && node->children != nullptr
			return node->children->operator[](i).get();
		}

		static bool at_least_one_child(const std::unique_ptr<trie_node>& node)
		{
			//assert node != nullptr
			if (node->children)
			{
				for (const auto& c : *node->children)
					if (c) return true;
			}
			return false;
		}

		static std::size_t index(const std::string& key, std::size_t i)
		{
			return key[i] - 'A';
		}

		std::unique_ptr<trie_node> insert(std::unique_ptr<trie_node> node, const std::string& key, std::size_t val, std::size_t depth)
		{
			if (!node)
				node.reset(new trie_node);
			if (depth == key.size())
			{
				if (node->val == npos) ++n;
				node->val = val;
				return node;
			}
			if (!node->children)
				node->children.reset(new std::array<std::unique_ptr<trie_node>, 26>);
			auto i = index(key, depth);
			child(node, i) = insert(std::move(child(node, i)), key, val, depth + 1);
			return node;
		}

		const trie_node* find_node(const trie_node* node, const std::string& key, std::size_t depth) const
		{
			if (!node)
				return nullptr;
			if (depth == key.size())
				return node;
			if (!node->children)
				return nullptr;
			auto i = index(key, depth);
			return find_node(child(node, i), key, depth + 1);
		}

		std::unique_ptr<trie_node> remove(std::unique_ptr<trie_node> node, const std::string& key, std::size_t depth, bool& removed)
		{
			if (!node)
				return nullptr;
			if (depth == key.size())
			{
				if (node->val != npos) --n;
				node->val = npos;
				removed = true;
			}
			else
			{
				if (node->children)
				{
					auto i = index(key, depth);
					child(node, i) = remove(std::move(child(node, i)), key, depth + 1, removed);
				}
			}
			if (node->val != npos || at_least_one_child(node))
				return node;
			return nullptr;
		}

		void keys(const trie_node* node, std::string prefix, std::vector<std::string>& acc) const
		{
			if (!node)
				return;
			if (node->val != npos) acc.push_back(prefix);
			if (node->children)
			{
				for (std::size_t i = 0; i < 26; ++i)
				{
					const trie_node* c = child(node, i);
					if (c) keys(c, prefix + static_cast<char>('A' + i), acc);
				}
			}
		}

		void keys_with_pattern(const trie_node* node, const std::string& pattern, std::string prefix, std::size_t depth, std::vector<std::string>& acc) const
		{
			if (!node)
				return;
			if (depth == pattern.size())
			{
				if (node->val != npos) acc.push_back(prefix);
				return;
			}
			if (node->children)
			{
				char ch = pattern[depth];
				if (ch == '_') //wildcard
				{
					for (std::size_t i = 0; i < 26; ++i)
					{
						const trie_node* c = child(node, i);
						if (c) keys_with_pattern(c, pattern, prefix + static_cast<char>('A' + i), depth + 1, acc);
					}
				}
				else
				{
					const trie_node* c = child(node, static_cast<std::size_t>(ch - 'A'));
					if (c) keys_with_pattern(c, pattern, prefix + ch, depth + 1, acc);
				}
			}
		}

	public:
		static const std::size_t npos = -1;

		void insert(const std::string& key, std::size_t val)
		{
			//assert key = [A, Z]*
			root = insert(std::move(root), key, val, 0);
		}

		std::size_t find(const std::string& key) const
		{
			//assert key = [A, Z]*
			const trie_node* node = find_node(root.get(), key, 0);
			return node ? node->val : npos;
		}

		bool remove(const std::string& key)
		{
			//assert key = [A, Z]*
			bool removed = false;
			root = remove(std::move(root), key, 0, removed);
			return removed;
		}

		std::size_t size() const
		{
			return n;
		}

		bool empty() const
		{
			return size() == 0;
		}

		std::vector<std::string> keys_with_prefix(const std::string& prefix) const
		{
			std::vector<std::string> acc;
			const trie_node* node = find_node(root.get(), prefix, 0);
			if (node) keys(node, prefix, acc);
			return acc;
		}

		std::vector<std::string> keys() const
		{
			return keys_with_prefix("");
		}

		std::vector<std::string> keys_with_pattern(const std::string& pattern) const
		{
			std::vector<std::string> acc;
			keys_with_pattern(root.get(), pattern, "", 0, acc);
			return acc;
		}

		void clear()
		{
			n = 0;
			root.reset(nullptr);
		}

	private:
		std::unique_ptr<trie_node> root;
		std::size_t n = 0;
	};
}

#endif /* TRIE_HPP */