CREATE TABLE waves (
  id VARCHAR PRIMARY KEY,
  name VARCHAR UNIQUE NOT NULL,
  released DATE NOT NULL
);
