class MinQueue {
	int upt;
	deque<ii> mq;

public:
	MinQueue () {
		upt = 0;
	}

	void add (int n) { // add value to the min
		int cnt = 0;
		while ((not mq.empty()) and n <= mq.back().ff) {
			cnt += mq.back().ss + 1;
			mq.pop_back();
		}
		mq.push_back(ii(n - upt, cnt));
	}

	int min () { // get min value
		if (mq.empty()) return 1e9;
		return mq.front().ff + upt;
	}

	void rmv () { // remove min value
		if (mq.empty()) return;
		if (mq.front().ss) {
			mq.front().ss--;
		} else {
			mq.pop_front();
		}
	}

	void upd (int n) { // add some value to all values
		upt += n;
	}
};