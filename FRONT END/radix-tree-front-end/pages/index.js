'use client';

import { useState, useEffect, useRef } from 'react';

export default function SearchBar() {
  const [query, setQuery] = useState('');
  const [suggestions, setSuggestions] = useState([]);
  const inputRef = useRef(null);
  const debounceRef = useRef(null);
  const [cursorIndex, setCursorIndex] = useState(0);
  const [highlightedIndex, setHighlightedIndex] = useState(-1);


  useEffect(() => {
    setHighlightedIndex(-1);
  }, [suggestions]);

  useEffect(() => {
    const handleKeyDown = (e) => {
      if (suggestions.length === 0) return;
  
      if (e.key === 'ArrowDown') {
        e.preventDefault();
        setHighlightedIndex((prev) => (prev + 1) % suggestions.length);
      } else if (e.key === 'ArrowUp') {
        e.preventDefault();
        setHighlightedIndex((prev) =>
          prev <= 0 ? suggestions.length - 1 : prev - 1
        );
      } else if (e.key === 'Enter') {
        if (highlightedIndex >= 0 && highlightedIndex < suggestions.length) {
          e.preventDefault();
          replaceWordAtCursor(suggestions[highlightedIndex]);
          setSuggestions([]);
          setHighlightedIndex(-1);
        }
      }
    };
  
    window.addEventListener('keydown', handleKeyDown);
    return () => window.removeEventListener('keydown', handleKeyDown);
  }, [suggestions, highlightedIndex]);
  

  useEffect(() => {
    if (debounceRef.current) {
      clearTimeout(debounceRef.current);
    }

    debounceRef.current = setTimeout(async () => {
      const word = extractCurrentWord(query, cursorIndex);
      if (!word) {
        setSuggestions([]);
        return;
      }

      try {
        const res = await fetch(`http://localhost:8080/${encodeURIComponent(word)}`);
        if (!res.ok) throw new Error('Fetch error');
        const data = await res.json();
        if(data){
          setSuggestions(data.suggestions || []);
        }
        else{
          setSuggestions([]);
        }
      } catch (err) {
        console.error('Error fetching:', err);
      }
    }, 50);

    return () => clearTimeout(debounceRef.current);
  }, [query, cursorIndex]);

  function extractCurrentWord(text, index) {
    const left = text.slice(0, index);
    const match = left.match(/(\S+)$/); // last word before cursor
    return match ? match[0] : '';
  }

  function replaceWordAtCursor(selected) {
    
    const input = inputRef.current; //grab the current input element(referring to inputRef)
    const start = query.slice(0, cursorIndex); //get the string to the left side of the cursor
    const end = query.slice(cursorIndex); //get the string to the right side of the cursor
  
    // Find the last word before the cursor
    const leftWordMatch = start.match(/(\S+)$/); //use regex to capture the last word immediately to the left of the cursor, if any.
    const leftWord = leftWordMatch ? leftWordMatch[0] : ''; 
    const leftIndex = leftWordMatch ? start.lastIndexOf(leftWord) : cursorIndex;
  
    // If there's a space right after the cursor, remove it
    const isRightSpace = end.startsWith(' ');
    const rightTrimmed = isRightSpace ? end.slice(1) : end; //conditional expression
  
    // Insert the selected word followed by exactly one space
    const newText = query.slice(0, leftIndex) + selected + ' ' + rightTrimmed;
    const newCursorPos = leftIndex + selected.length + 1;
  
    setQuery(newText); //set the value of search bar to the newly assembled text
  
    requestAnimationFrame(() => {
      if (input) {
        input.setSelectionRange(newCursorPos, newCursorPos);
        input.focus();
        setCursorIndex(newCursorPos);
      }
    }); //ensure the input field has been updated before we manually apply the change in cursor location
  
    setSuggestions([]);
  }
  return(
    <div className="min-h-screen bg-gradient-to-bl from-gray-800 via-gray-900 to-black pt-32">
      <div className="flex flex-col items-center w-full">
        <h1 className="text-5xl font-bold mb-6 text-white">Goggle</h1>
        <div className="relative w-1/2">
          <input
            ref={inputRef}
            type="text"
            value={query}
            onChange={(e) => {
              setQuery(e.target.value);
              setCursorIndex(e.target.selectionStart);
            }}
            onClick={(e) => setCursorIndex(e.target.selectionStart)}
            onKeyUp={(e) => setCursorIndex(e.target.selectionStart)}
            className="w-full caret-white text-white p-4 border border-gray-300 rounded-full shadow-md focus:outline-none focus:ring-2 focus:ring-blue-500"
            placeholder="Search..."
          />
          {suggestions.length > 0 && (
            <div className="absolute mt-2 w-full bg-white border rounded shadow">
              {suggestions.map((suggestion, index) => (
                <div
                  key={index}
                  className={`px-4 py-2 cursor-pointer ${
                    index === highlightedIndex ? 'bg-blue-100' : ''
                  }`}
                  onMouseEnter={() => setHighlightedIndex(index)}
                  onClick={() => {
                    replaceWordAtCursor(suggestion);
                    setSuggestions([]);
                    setHighlightedIndex(-1);
                  }}
                >
                  {suggestion}
                </div>
              ))}
            </div>
          )}
        </div>
      </div>
    </div>

  );

}
