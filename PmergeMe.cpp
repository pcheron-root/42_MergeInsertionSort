
// ************************************************************************** //
//	UTILS
// ************************************************************************** //

int getMultipleOfTwo(bool refresh)
{
	static int nbr = 4;

	if (refresh)
		nbr = 4;
	int	to_return = nbr;
	nbr *= 2;
	return (to_return);
}

int getDuoJacobsthalNbr(bool refresh)
{
	static int js = 1;
	static int js_last = 3;
	
	if (refresh)
	{
		js = 1;
		js_last = 3;
	}
	int	to_return = js_last - js;
	int	tmp = js;
	js = js_last;
	js_last = to_return + 2 * tmp;
	return (to_return);		
}

template <typename v_d>
void	updateIndex(size_t min, size_t max, v_d& vect, int range)
{
	size_t	size = vect.size();

	for (size_t i = 0; i < size; ++i)
	{
		if (vect[i] > max)
			return ;
		else if (vect[i] >= min)
			vect[i] += range;
	}
}

template <typename v_d>
size_t	whereInsert(v_d v, std::vector<size_t>& sortedIndexes, int nbrToInsert, int indexMax)
{
	int	indexMin = 0;
	int index_mid;

	if (indexMax + 1 > static_cast<int>(sortedIndexes.size()))
		indexMax = sortedIndexes.size() - 1;
	

	while (indexMin + 1 != indexMax)
	{
		index_mid = indexMin + (indexMax - indexMin) / 2;
		if (v[sortedIndexes[index_mid]] < to_insert)
			indexMin = index_mid;
		else
			indexMax = index_mid;
	}
	if (v[sortedIndexes[indexMin]] > to_insert)
		return (sortedIndexes[indexMin]);
	if (v[sortedIndexes[indexMax]] < to_insert)
		return (sortedIndexes[indexMax] + sortedIndexes[0] + 1);
	if (sortedIndexes[indexMax] - sortedIndexes[indexMin] == sortedIndexes[0] + 1)
		return (sortedIndexes[indexMax]);
	return (sortedIndexes[indexMax] - sortedIndexes[0] - 1);
}

template <typename v_d>
void	insertion(v_d& nbrs, size_t range) {
	
	std::vector<size_t> sortedIndexes;
	std::vector<size_t> unsortedIndexes;

	size_t	size = nbrs.size();
	for (size_t i = range - 1; i < size; i += range)
	{
		if (i < 2 * range || i / range % 2)
			sortedIndexes.push_back(i);
		else
			unsortedIndexes.push_back(i);
	}

	int	duoJacobsthalNbr = getDuoJacobsthalNbr(true);
	int	indexMax = getMultipleOfTwo(true) - 1;
	while (unsortedIndexes.empty() == false)
	{
		for (int ind = std::min(duoJacobsthalNbr, static_cast<int>(unsortedIndexes.size())) - 1; ind > -1; --ind)
		{
			size_t	whereInsert = where_i_have_to_go(nbrs, sortedIndexes, nbrs[unsortedIndexes[ind]], indexMax);
			size_t	whereImFrom = unsortedIndexes[ind];

			for (size_t j = 0; j < range; j++)
			{
				nbrs.insert(nbrs.begin() + whereInsert - range + 1, nbrs[whereImFrom]);
				nbrs.erase(nbrs.begin() + whereImFrom + 1);
			}

			unsortedIndexes.erase(unsortedIndexes.begin() + ind);
			upgrade_ind(whereInsert, whereImFrom, sortedIndexes, range);
			upgrade_ind(whereInsert, whereImFrom, unsortedIndexes, range);
			sortedIndexes.insert(std::lower_bound(sortedIndexes.begin(), sortedIndexes.end(), whereInsert), whereInsert);
		}
		duoJacobsthalNbr = getDuoJacobsthalNbr(false);
		indexMax = getMultipleOfTwo(false) - 1;
	}
}

// ************************************************************************** //
//	MERGE
// ************************************************************************** //

void	mergeInsertion(std::vector<int>& nbrs, int range)
{
    std::vector<int>::iterator left = nbrs.begin() + size - 1;
    std::vector<int>::iterator right = nbrs.begin() + 2 * size - 1;

    int nbIteration = nbrs.size() / size / 2;

    if (nbIteration == 0)
        return ;
    for (int it = 0; it < nbIteration; it++, left += size * 2, right += size * 2)
    {
        if (*left > *right)
            swapPair(left, size);
    }
	mergeInsertion(nbrs, range * 2);
	insertion(nbrs, size);
}

