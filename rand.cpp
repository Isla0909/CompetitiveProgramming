int rand(int l, int r)//[l, r]
{
	return rng() % (r - l + 1) + l;
}

double random(double l, double r)
{
	return 1.0 * rng() / rng.max() * (r - l) + l;
}