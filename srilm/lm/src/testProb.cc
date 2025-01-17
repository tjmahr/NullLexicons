/*
 * testProb --
 *	Test arithmetic with log probabilities
 */

#ifndef lint
static char Copyright[] = "Copyright (c) 2000-2006 SRI International, 2012 Microsoft Corp.  All Rights Reserved.";
static char RcsId[] = "@(#)$Header: /home/srilm/CVS/srilm/lm/src/testProb.cc,v 1.10 2012/12/18 01:14:04 stolcke Exp $";
#endif


#ifdef PRE_ISO_CXX
# include <iostream.h>
#else
# include <iostream>
using namespace std;
#endif
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "Prob.h"

/*
 * Simulate the rounding going on from the original LM LogP scores to the
 * bytelogs in the recognizer:
 * - PFSGs encode LogP as intlogs
 * - Nodearray compiler maps intlogs to bytelogs
 */
#define RoundToBytelog(x)	BytelogToLogP(IntlogToBytelog(LogPtoIntlog(x)))

int
main(int argc, char **argv)
{
    if (argc < 2) {
    	cerr << "usage: testProb p1 [p2]\n";
	exit(2);
    }

    cout << "log(0) = " << LogP_Zero << " ; isfinite = " << isfinite(LogP_Zero) << endl;
    cout << "log(inf) = " << LogP_Inf << " ; isfinite = " << isfinite(LogP_Inf) << endl;
    double n = 0.0;
    n = n / 0.0;
    cout << "NaN = " << n << " ; isnan = " << isnan(n) << endl;

    if (argc < 3) {
    	Prob p;

	sscanf(argv[1], "%lf", &p);
	LogP lp = ProbToLogP(p);

    	cout << "log(p) = " << lp << " " << LogPtoProb(lp) << endl;

	char buffer[200];
	LogP lp2;

	sprintf(buffer, "%lf ", lp);
	if (parseLogP(buffer, lp2)) {
		cout << "lp read back = " << lp2 << endl;
	} else {
		cout << "lp read back FAILED\n";
	}

    	cout << "Decipher log(p) = " << RoundToBytelog(lp)
		<< " " << LogPtoProb(RoundToBytelog(lp))
		<< " " << LogPtoIntlog(lp)
		<< " " << IntlogToBytelog(LogPtoIntlog(lp)) << endl;
    } else {
    	Prob p, q;

	sscanf(argv[1], "%lf", &p);
	sscanf(argv[2], "%lf", &q);

	LogP lp = ProbToLogP(p);
	LogP lq = ProbToLogP(q);
	LogP lpq = AddLogP(lp,lq);

    	cout << "log(p + q) = " << lpq << " " << LogPtoProb(lpq) << endl;

	if (lp >= lq) {
	    lpq = SubLogP(lp,lq);

	    cout << "log(p - q) = " << lpq << " " << LogPtoProb(lpq) << endl;
	}
    }

    exit(0);
}
