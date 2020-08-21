// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/foreach.hpp>

#include "checkpoints.h"

#include "db.h"
#include "main.h"
#include "uint256.h"

namespace Checkpoints
{
    typedef std::map<int, uint256> MapCheckpoints;

    //
    // What makes a good checkpoint block?
    // + Is surrounded by blocks with reasonable timestamps
    //   (no blocks before with a timestamp after, none after with
    //    timestamp before)
    // + Contains no strange transactions
    //
    static MapCheckpoints mapCheckpoints =
        boost::assign::map_list_of
	(       0, hashGenesisBlockOfficial )
	(      10, uint256("0x0000074074af28e73189ae5767b706246be2e0827c46d97a61178394aec877cf"))
	(    1000, uint256("0x00000000009a77d895a12394d2fc903cea7d3ff1f9c4b4f41c5fb0e4d3c360be"))    
	(   31781, uint256("0x42265210870957b8d37f91a0834c6cda65949b2ca805bb3a7d527a4cd585a090")) //official hyp fork
	(   50001, uint256("0xde83ae1239df91ef9ea824adeef2d49092598c393b966cba199a61d8f2911990"))
	(   80987, uint256("0x6b943fa756e915ddd8b654844781e21090ae9ddfcb2147fba46cac529df5be08")) //not using even number because sync gets sticky
	(  100001, uint256("0x9fc679b3de32e866a48814b44900d41279b2a5b6bf211470f706a4eaf86668e4"))
	(  150001, uint256("0xe41a948462ce5d6f2721919fc4f564ab13261dab08adb60561b6c13669164a41"))
	(  199999, uint256("0x084b314dfee7db9d311a5db4dc4b8880df36eb7e9bb90ec98dd0bab5af2a7df2"))
	(  235691, uint256("0xf0f71ea7edf7457e611ee893cdbb6ff19499713f4dae935d6d21e073d96a7dc3"))
	(  235999, uint256("0xafe60dd0ab56ef529db21ea648ea4fd8de758a11b6a8ac1fa5cd2d4959162106"))
	(  399999, uint256("0x875356232916a420c100b83d87cc9ce3eb9a174750b48d2fd1eefba7292163b5"))
	(  499999, uint256("0x8e370d8ab8bdb6e6a5a4882dda755b23b5f284f633e04c12e6f73f92de15e68e"))
	(  699999, uint256("0x718d1acc5524198b43695b7b38b722631a44b22266412016278c664de4d90d74"))
	(  899999, uint256("0xe36df1a400d776d226dc56ffb8a9f7448dde3149cdc1ba27c0babba113f4ba14"))
	( 1099999, uint256("0x2183b8c080e20e8b8463834579b60cbcb79b8cfb670681b306ea6dc9f194c34c"))
    	( 1207950, uint256("0xbad0a0f14081129f34d42fdc617638756158fd7b1413f4d3a2916bed2c1a61d4"))
    	( 1377570, uint256("0x3d76cad9c096ce48336da1528ab31b5897eac41b8780fb37f64110ca034f971c"))
	( 1600000, uint256("0x3ccdbe43142c8a65a72e365ea8b8982479090fbf5edb5d510870d420184c6e9b"))
	( 1800000, uint256("0xa65739d5c0b158577c1b4865d242530b59230bf23d66cd1c84d492a5754c51f6"))
	( 2000000, uint256("0x68bf106147f695446037ffeeb0069fa1fb8e1866c8c4b6cfb2cdcfe433854558"))
    	( 2068897, uint256("0x6f9ef83d8fd4bd0d3b44a3da22e86122a08133351206cf2434c815d0d53b9a67"))
	( 2077813, uint256("0x6cdf607acebef2dcae601ab143b0c161e52f0c22445cf2b3bbc9130c3537284b"))
	( 2102337, uint256("0x044ebbb95005290b0db3804e2c4854114911696674edf4afc6a707b07deccff3"))
	( 2146142, uint256("0x8c34bc27e5b53fbc2b3a2d2dac4c9809a79fdf686fd5a63f6ba0e16dbc227f99"))
	;

    static MapCheckpoints mapCheckpointsTestnet =
        boost::assign::map_list_of
        ( 0, hashGenesisBlockTestNet )
		(70, uint256("0x97c81df9aab50f1bef2e09ec8d806c3cc7ec6b7b7f13c70f1b854d8e40ed77c9"))
        ;

    bool CheckHardened(int nHeight, const uint256& hash)
    {
        MapCheckpoints& checkpoints = (fTestNet ? mapCheckpointsTestnet : mapCheckpoints);

        MapCheckpoints::const_iterator i = checkpoints.find(nHeight);
        if (i == checkpoints.end()) return true;
        return hash == i->second;
    }

    int GetTotalBlocksEstimate()
    {
        MapCheckpoints& checkpoints = (fTestNet ? mapCheckpointsTestnet : mapCheckpoints);

        return checkpoints.rbegin()->first;
    }

    CBlockIndex* GetLastCheckpoint(const std::map<uint256, CBlockIndex*>& mapBlockIndex)
    {
        MapCheckpoints& checkpoints = (fTestNet ? mapCheckpointsTestnet : mapCheckpoints);

        BOOST_REVERSE_FOREACH(const MapCheckpoints::value_type& i, checkpoints)
        {
            const uint256& hash = i.second;
            std::map<uint256, CBlockIndex*>::const_iterator t = mapBlockIndex.find(hash);
            if (t != mapBlockIndex.end())
                return t->second;
        }
        return NULL;
    }
}
