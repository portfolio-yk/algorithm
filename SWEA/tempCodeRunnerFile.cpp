for (auto it = fail_slot.begin(); it != fail_slot.end(); ++it) {
        if (it->number == mCarNo) {
            fail_slot.erase(it);
            break;
        }
    }