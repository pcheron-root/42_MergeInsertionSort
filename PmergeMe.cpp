
// ************************************************************************** //
//	INSERTION UTILS
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
	static int jsLast = 3;
	
	if (refresh)
	{
		js = 1;
		jsLast = 3;
	}
	int	to_return = jsLast - js;
	int	tmp = js;
	js = jsLast;
	jsLast = to_return + 2 * tmp;
	return (to_return);		
}

template <typename T>
void	updateIndex(size_t min, size_t max, T& vect, int range)
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

// ************************************************************************** //
//	INSERTION PART
// ************************************************************************** //

template <typename T>
size_t	whereInsert(T v, std::vector<size_t>& sortedIndexes, int nbrToInsert, int indexMax)
{
	int	indexMin = 0;
	int indexMid;

	if (indexMax + 1 > static_cast<int>(sortedIndexes.size()))
		indexMax = sortedIndexes.size() - 1;
	

	while (indexMin + 1 != indexMax)
	{
		indexMid = indexMin + (indexMax - indexMin) / 2;
		if (v[sortedIndexes[indexMid]] < nbrToInsert)
			indexMin = indexMid;
		else
			indexMax = indexMid;
	}
	if (v[sortedIndexes[indexMin]] > nbrToInsert)
		return (sortedIndexes[indexMin]);
	if (v[sortedIndexes[indexMax]] < nbrToInsert)
		return (sortedIndexes[indexMax] + sortedIndexes[0] + 1);
	if (sortedIndexes[indexMax] - sortedIndexes[indexMin] == sortedIndexes[0] + 1)
		return (sortedIndexes[indexMax]);
	return (sortedIndexes[indexMax] - sortedIndexes[0] - 1);
}

template <typename T>
void	insertion(T& nbrs, size_t range) {

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

	int		duoJacobsthalNbr = getDuoJacobsthalNbr(true);
	int		indexMax = getMultipleOfTwo(true) - 1;
	size_t	whereInsertMe, whereImFrom;

	while (unsortedIndexes.empty() == false)
	{
		for (int ind = std::min(duoJacobsthalNbr, static_cast<int>(unsortedIndexes.size())) - 1; ind > -1; --ind)
		{
			whereInsertMe = whereInsert(nbrs, sortedIndexes, nbrs[unsortedIndexes[ind]], indexMax);
			whereImFrom = unsortedIndexes[ind];
			for (size_t j = 0; j < range; j++)
			{
				nbrs.insert(nbrs.begin() + whereInsertMe - range + 1, nbrs[whereImFrom]);
				nbrs.erase(nbrs.begin() + whereImFrom + 1);
			}
			unsortedIndexes.erase(unsortedIndexes.begin() + ind);
			upgrade_ind(whereInsertMe, whereImFrom, sortedIndexes, range);
			upgrade_ind(whereInsertMe, whereImFrom, unsortedIndexes, range);
			sortedIndexes.insert(std::lower_bound(sortedIndexes.begin(), sortedIndexes.end(), whereInsertMe), whereInsertMe);
		}
		duoJacobsthalNbr = getDuoJacobsthalNbr(false);
		indexMax = getMultipleOfTwo(false) - 1;
	}
}

// ************************************************************************** //
//	MERGE PART
// ************************************************************************** //

template <typename T>
void	mergeInsertion(T& nbrs, int range)
{
    T::iterator left = nbrs.begin() + range - 1;
    T::iterator right = nbrs.begin() + 2 * range - 1;

    int nbIteration = nbrs.size() / range / 2;

    if (nbIteration == 0)
        return ;
    for (int it = 0; it < nbIteration; it++, left += range * 2, right += range * 2)
    {
        if (*left > *right)
            swapPair(left, range);
    }
	mergeInsertion(nbrs, range * 2);
	insertion(nbrs, range);
}
