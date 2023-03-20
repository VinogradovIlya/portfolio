package DatedMap;

import java.time.Instant;
import java.util.Date;
import java.util.HashMap;
import java.util.Map;
import java.util.Set;

public class DatedMapImpl implements DatedMap {
    private Map<String, String> map = new HashMap<>();
    private Map<String, Instant> dateMap = new HashMap<>();

    public void put(String key, String value) {
        map.put(key, value);
        dateMap.put(key, Instant.now());
    }

    public String get(String key) {
        return map.get(key);
    }

    public boolean containsKey(String key) {
        return map.containsKey(key);
    }

    public void remove(String key) {
        map.remove(key);
    }

    public Set<String> keySet() {
        return map.keySet();
    }

    public Date getKeyLastInsertionDate(String key) { 
        if (dateMap.containsKey(key)) {
            return Date.from(dateMap.get(key));
        } else
            return null;
    }
}