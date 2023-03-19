package DatedMap;

import java.util.Date;
import java.util.HashMap;
import java.util.Map;
import java.util.Set;

public class DatedMapImpl implements DatedMap {
    private String key, value;
    private Date date;
    private Map<String, DatedMapImpl> map = new HashMap<>();

    public DatedMapImpl(String value) {
        this.value = value;
        this.date = new Date();
    }
    
    public void put(String key, String value) {
        map.put(key, new DatedMapImpl(value));
    }

    public String get(String key) {
        return getValue();
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
        if (map.containsKey(key)) {
            return map.get(key).getDate();
        } else
            return null;
    }

    public String getValue() {
        return value;
    }

    public Date getDate() {
        return date;
    }
}