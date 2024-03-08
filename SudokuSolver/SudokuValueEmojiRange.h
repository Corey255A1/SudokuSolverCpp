/*
 * WunderVision 2024
 */
#ifndef HSudokuValueEmojiRange
#define HSudokuValueEmojiRange
#include "SudokuValueRange.h"
#include "SudokuValueEmoji.h"
#include <unordered_map>
class SudokuValueEmojiRange : public SudokuValueRange
{
private:
    std::vector<std::wstring> m_emojis;
    std::wstring m_invalidEmoji;
    std::wstring m_beginEmoji;
    std::wstring m_endEmoji;
    int m_invalid;
    size_t m_count;

public:
    SudokuValueEmojiRange(const std::vector<std::wstring> &emojis) : m_invalid{0},
                                                                    m_emojis{emojis},
                                                                    m_count{emojis.size() - 1}
    {
        m_invalidEmoji = m_emojis[m_invalid];
        m_beginEmoji = m_emojis[m_invalid + 1];
        m_endEmoji = m_emojis[m_count];
    }

    virtual std::unique_ptr<SudokuValue> getMin() const { return makeValue(m_invalid + 1); }
    virtual std::unique_ptr<SudokuValue> getMax() const { return makeValue(m_count); }
    virtual size_t getCount() const { return m_count; }

    virtual std::unique_ptr<SudokuValue> getNext(const SudokuValue *value) const
    {
        return makeValue(SudokuValueEmoji::castTo(value)->getValue() + 1);
    }

    virtual std::unique_ptr<SudokuValue> getPrevious(const SudokuValue *value) const
    {
        return makeValue(SudokuValueEmoji::castTo(value)->getValue() - 1);
    }

    virtual bool isDefault(const SudokuValue *value) const
    {
        return SudokuValueEmoji::castTo(value)->getValue() == m_invalid;
    }

    virtual std::unique_ptr<SudokuValue> makeDefault() const
    {
        return makeValue(m_invalid);
    }

    virtual std::unique_ptr<SudokuValue> parseStream(std::wstringstream& stream) const
    {
        std::wstring emojiValue;
        stream >> emojiValue;
        auto emojiItr = std::find(m_emojis.begin(), m_emojis.end(), emojiValue);
        if (emojiItr == m_emojis.end())
        {
            return makeDefault();
        }
        if (emojiItr == m_emojis.begin())
        {
            return makeDefault();
        }

        int index = emojiItr - m_emojis.begin();
        return makeValue(index);
    }

    std::unique_ptr<SudokuValue> makeValue(int index) const
    {
        if(index >= m_emojis.size()){
            return makeDefault();
        }
        return std::make_unique<SudokuValueEmoji>(shared_from_this(), index, m_emojis[index]);
    }
};
#endif