// Insert student data
document.getElementById("insertForm").addEventListener("submit", function(event) {
  event.preventDefault();

  const formData = new FormData(this);
  const formObject = {};

  formData.forEach((value, key) => {
      formObject[key] = value;
  });

  fetch("http://localhost:5500/insert", {  // Updated port
      method: "POST",
      headers: {
          "Content-Type": "application/x-www-form-urlencoded"
      },
      body: new URLSearchParams(formObject)
  })
  .then(response => response.text())
  .then(data => alert(data))
  .catch(error => console.error('Error:', error));
});

// Search student by ID
document.getElementById("searchForm").addEventListener("submit", function(event) {
  event.preventDefault();

  const searchId = document.getElementById("searchId").value;
  fetch(`http://localhost:8080/search?id=${searchId}`)  // Updated port
  .then(response => response.text())
  .then(data => {
      document.getElementById("studentDetails").innerText = data;
  })
  .catch(error => console.error('Error:', error));
});
