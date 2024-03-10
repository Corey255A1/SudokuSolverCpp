/*
 * WunderVision 2024
 * Generic Value Base Class
 */
#ifndef HSudokuValue
#define HSudokuValue
#include <iostream>
#include <functional>
#include <memory>

class SudokuValueRange;
class SudokuValue
{
protected:
	std::shared_ptr<const SudokuValueRange> m_values;

public:
	SudokuValue(std::shared_ptr<const SudokuValueRange> values);
	virtual size_t getHash() const = 0;
	virtual bool equals(const SudokuValue *right) const = 0;
	virtual bool lessThan(const SudokuValue *right) const = 0;
	virtual bool lessThanOrEqual(const SudokuValue *right) const = 0;
	virtual std::unique_ptr<SudokuValue> makeCopy() const = 0;
	virtual std::ostream &outToStream(std::ostream &stream) const = 0;
	virtual std::wostream &outToStream(std::wostream &stream) const = 0;
	std::shared_ptr<const SudokuValueRange> getValueRange() const;
	bool isDefault() const;
	friend std::ostream &operator<<(std::ostream &os, const SudokuValue &dt)
	{
		return dt.outToStream(os);
	}
	friend std::wostream &operator<<(std::wostream &os, const SudokuValue &dt)
	{
		return dt.outToStream(os);
	}
};

template <>
struct std::hash<SudokuValue>
{
	size_t operator()(const SudokuValue &value) const
	{
		return value.getHash();
	}
};

template <>
struct std::equal_to<SudokuValue>
{
	bool operator()(const SudokuValue &left, const SudokuValue &right) const
	{
		return left.equals(&right);
	}
};

struct SudokuValueOps
{
	size_t operator()(const std::unique_ptr<SudokuValue> &value) const
	{
		return value->getHash();
	}
	bool operator()(const std::unique_ptr<SudokuValue> &left, const std::shared_ptr<SudokuValue> &right) const
	{
		return left->equals(right.get());
	}

	size_t operator()(const std::shared_ptr<SudokuValue> &value) const
	{
		return value->getHash();
	}
	bool operator()(const std::shared_ptr<SudokuValue> &left, const std::shared_ptr<SudokuValue> &right) const
	{
		return left->equals(right.get());
	}
};

struct SudokuValueLT
{
	bool operator()(const std::unique_ptr<SudokuValue> &left, const std::unique_ptr<SudokuValue> &right) const
	{
		return left->lessThan(right.get());
	}
	bool operator()(const std::unique_ptr<SudokuValue> &left, const SudokuValue *right) const
	{
		return left->lessThan(right);
	}
	bool operator()(const SudokuValue *left, const std::unique_ptr<SudokuValue> &right) const
	{
		return left->lessThan(right.get());
	}

	bool operator()(const std::shared_ptr<SudokuValue> &left, const std::shared_ptr<SudokuValue> &right) const
	{
		return left->lessThan(right.get());
	}
	bool operator()(const std::shared_ptr<SudokuValue> &left, const SudokuValue *right) const
	{
		return left->lessThan(right);
	}
	bool operator()(const SudokuValue *left, const std::shared_ptr<SudokuValue> &right) const
	{
		return left->lessThan(right.get());
	}
};

#endif