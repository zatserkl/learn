def longest_consequtive(text):
    """
    Initial version (after fixing errors).
    """
    """
    My opinion about this code:
        I don't need in fact to keep frequencies of all letter.
        Just enough to keep the maximum result.
    """
    if len(text) == 0:
        return {}

    all_letters = {}

    current_letter = text[0]
    current_count = 1

    for letter in text[1:]:
        if letter == current_letter:
            current_count += 1
        else:
            # new letter is different from the current
            if current_letter in all_letters:
                if all_letters[current_letter] < current_count:
                    all_letters[current_letter] = current_count
            else:
                all_letters[current_letter] = current_count

            # start following the new letter
            current_letter = letter
            current_count = 1

    # return the result
    max_letter = list(all_letters.keys())[0]
    max_count = all_letters[max_letter]

    for letter in list(all_letters.keys())[1:]:
        if all_letters[letter] > max_count:
            max_letter = letter
            max_count = all_letters[max_letter]

    return {max_letter: max_count}


text = 'AABCDDBBBEA'
print(longest_consequtive(text))
