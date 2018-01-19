/*
 * This software is distributed under BSD 3-clause license (see LICENSE file).
 *
 * Authors: Soeren Sonnenburg, Sergey Lisitsyn
 */

#include <shogun/lib/config.h>
#include <shogun/lib/common.h>
#include <shogun/io/SGIO.h>
#include <shogun/distance/ChebyshewMetric.h>
#include <shogun/features/Features.h>

using namespace shogun;

CChebyshewMetric::CChebyshewMetric() : CDenseDistance<float64_t>()
{
}

CChebyshewMetric::CChebyshewMetric(CDenseFeatures<float64_t>* l, CDenseFeatures<float64_t>* r)
: CDenseDistance<float64_t>()
{
	init(l, r);
}

CChebyshewMetric::~CChebyshewMetric()
{
	cleanup();
}

bool CChebyshewMetric::init(CFeatures* l, CFeatures* r)
{
	return CDenseDistance<float64_t>::init(l,r);
}

void CChebyshewMetric::cleanup()
{
}

float64_t CChebyshewMetric::compute(int32_t idx_a, int32_t idx_b)
{
	int32_t alen, blen;
	bool afree, bfree;

	float64_t* avec=
		((CDenseFeatures<float64_t>*) lhs)->get_feature_vector(idx_a, alen, afree);
	float64_t* bvec=
		((CDenseFeatures<float64_t>*) rhs)->get_feature_vector(idx_b, blen, bfree);

	ASSERT(alen==blen)

	float64_t result=DBL_MIN;

	for (int32_t i=0; i<alen; i++)
		result=CMath::max(result, fabs(avec[i]-bvec[i]));

	((CDenseFeatures<float64_t>*) lhs)->free_feature_vector(avec, idx_a, afree);
	((CDenseFeatures<float64_t>*) rhs)->free_feature_vector(bvec, idx_b, bfree);

	return result;
}
