import re
import pandas as pd
from nltk.tokenize import word_tokenize
from nltk.corpus import stopwords
from nltk.stem.wordnet import WordNetLemmatizer

data = pd.read_csv("../reviews.csv")
data['label'] = data['sentiment'].apply(lambda l: 1 if l == "positive" else 0)

def preprocess(text) -> str:
    if not hasattr(preprocess, "stopwords"):
        preprocess.stopwords = set(stopwords.words("english"))
        preprocess.lemmatizer = WordNetLemmatizer()

    text = re.sub(r"<.*>|\d", r'', text)
    text = re.sub(r"\W|\s+", r' ', text)
    text = text.lower()
    text = word_tokenize(text)
    text = [w for w in text if w not in preprocess.stopwords]
    text = [preprocess.lemmatizer.lemmatize(w) for w in text]
    text = [w for w in text if w not in preprocess.stopwords]
    return text


data['review'] = data['review'].apply(preprocess)
print(data)
data[["review", "label"]].to_csv('../reviews_preprocessed.csv', index=False, header=True)
print("Saved as 'reviews_preprocessed.csv'")
